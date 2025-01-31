#include "com_jcy_ndk_nativeC_ffmpeg_FFmpegPalyer.h"
#include <time.h>

//封装格式
#include "include/libavformat/avformat.h"
//解码
#include "include/libavcodec/avcodec.h"
//缩放
#include "include/libswscale/swscale.h"


#include <android/log.h>
#include <ffmpeg/include/libavutil/time.h>
#include <jni.h>

#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "jcy", format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "jcy", format, ##__VA_ARGS__)

JNIEXPORT void JNICALL Java_com_jcy_ndk_nativeC_ffmpeg_FFmpegPalyer_push
        (JNIEnv *env, jobject obj, jstring input_jstr, jstring output_jstr) {
    //java string->c char*
    const char *input_cstr = (*env)->GetStringUTFChars(env, input_jstr, JNI_FALSE);
    const char *output_cstr = (*env)->GetStringUTFChars(env, output_jstr, JNI_FALSE);
    int videoindex = -1;
    //所有代码执行之前要调用av_register_all和avformat_network_init
    //初始化所有的封装和解封装 flv mp4 mp3 mov。不包含编码和解码
    av_register_all();

    //初始化网络库
    avformat_network_init();

    //////////////////////////////////////////////////////////////////
    //                   输入流处理部分
    /////////////////////////////////////////////////////////////////
    //打开文件，解封装 avformat_open_input
    //AVFormatContext **ps  输入封装的上下文。包含所有的格式内容和所有的IO。如果是文件就是文件IO，网络就对应网络IO
    //const char *url  路径
    //AVInputFormt * fmt 封装器
    //AVDictionary ** options 参数设置
    AVFormatContext *ictx = NULL;

    AVOutputFormat *ofmt = NULL;

    //打开文件，解封文件头
    int ret = avformat_open_input(&ictx, input_cstr, 0, NULL);
    if (ret < 0) {
        LOGE("无法获取文件信息");
        goto end;
    }
    LOGE("avformat_open_input success!");
    //获取音频视频的信息 .h264 flv 没有头信息
    ret = avformat_find_stream_info(ictx, 0);
    if (ret != 0) {
        LOGE("无法获取文件信息");
        goto end;
    }
    //打印视频视频信息
    //0打印所有  inUrl 打印时候显示，
    av_dump_format(ictx, 0, input_cstr, 0);

    //////////////////////////////////////////////////////////////////
    //                   输出流处理部分
    /////////////////////////////////////////////////////////////////
    AVFormatContext * octx = NULL;
    //如果是输入文件 flv可以不传，可以从文件中判断。如果是流则必须传
    //创建输出上下文
    ret = avformat_alloc_output_context2(&octx, NULL, "flv", output_jstr);
    if (ret < 0) {
        LOGE("无法创建输出上下文");
        goto end;
    }
    LOGE("avformat_alloc_output_context2 success!");

    ofmt = octx->oformat;
    int i;
    //for (i = 0; i < ictx->nb_streams; i++) {
    //  cout << "i " << i <<"  "<< ictx->nb_streams<< endl;
    //  AVStream *in_stream = ictx->streams[i];
    //  AVCodec *codec = avcodec_find_decoder(in_stream->codecpar->codec_id);
    //  AVStream *out_stream = avformat_new_stream(octx, codec);
    //  if (!out_stream) {
    //      printf("Failed allocating output stream\n");
    //      ret = AVERROR_UNKNOWN;
    //  }
    //  AVCodecContext *pCodecCtx = avcodec_alloc_context3(codec);
    //  ret = avcodec_parameters_to_context(pCodecCtx, in_stream->codecpar);
    //  if (ret < 0) {
    //      printf("Failed to copy context input to output stream codec context\n");
    //  }
    //  pCodecCtx->codec_tag = 0;
    //  if (octx->oformat->flags & AVFMT_GLOBALHEADER) {
    //      pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
    //  }
    //  ret = avcodec_parameters_from_context(out_stream->codecpar, pCodecCtx);
    //  if (ret < 0) {
    //      printf("Failed to copy context input to output stream codec context\n");
    //  }
    //}

    for (i = 0; i < ictx->nb_streams; i++) {
        //获取输入视频流
        AVStream *in_stream = ictx->streams[i];
        //为输出上下文添加音视频流（初始化一个音视频流容器）
        AVStream *out_stream = avformat_new_stream(octx, in_stream->codec->codec);
        if (!out_stream) {
            printf("未能成功添加音视频流\n");
            ret = AVERROR_UNKNOWN;
        }

        //将输入编解码器上下文信息 copy 给输出编解码器上下文
        //ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
//        ret = avcodec_parameters_copy(out_stream->codecpar, in_stream->codecpar);
        ret = avcodec_parameters_copy(out_stream->codec, in_stream->codec);
        //ret = avcodec_parameters_from_context(out_stream->codecpar, in_stream->codec);
        //ret = avcodec_parameters_to_context(out_stream->codec, in_stream->codecpar);
        if (ret < 0) {
            printf("copy 编解码器上下文失败\n");
        }
        out_stream->codec->codec_tag = 0;

        out_stream->codec->codec_tag = 0;
        if (octx->oformat->flags & AVFMT_GLOBALHEADER) {
            out_stream->codec->flags = out_stream->codec->flags | CODEC_FLAG_GLOBAL_HEADER;
        }
    }

    //输入流数据的数量循环
    for (i = 0; i < ictx->nb_streams; i++) {
        if (ictx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoindex = i;
            break;
        }
    }

    av_dump_format(octx, 0, output_jstr, 1);

    //////////////////////////////////////////////////////////////////
    //                   准备推流
    /////////////////////////////////////////////////////////////////

    //打开IO
    //打开输出的AVIOContext IO流上下文
    if (!(ofmt->flags & AVFMT_NOFILE)) {
        ret = avio_open(&octx->pb, output_cstr, AVIO_FLAG_WRITE);
    }
    if (ret < 0) {
        LOGE("无法打开IO");
        goto end;
    }

    //写入头部信息
    ret = avformat_write_header(octx, 0);
    if (ret < 0) {
        LOGE("写入头部信息");
        goto end;
    }
    LOGE("avformat_write_header Success!");
    //推流每一帧数据
    //int64_t pts  [ pts*(num/den)  第几秒显示]
    //int64_t dts  解码时间 [P帧(相对于上一帧的变化) I帧(关键帧，完整的数据) B帧(上一帧和下一帧的变化)]  有了B帧压缩率更高。
    //uint8_t *data
    //int size
    //int stream_index
    //int flag
    AVPacket pkt;
    //获取当前的时间戳  微妙
    long long start_time = av_gettime();
    long long frame_index = 0;
    while (1) {
        //输入输出视频流
        AVStream *in_stream, *out_stream;
        //获取解码前数据
        ret = av_read_frame(ictx, &pkt);
        if (ret < 0) {
            break;
        }

        /*
        PTS（Presentation Time Stamp）显示播放时间
        DTS（Decoding Time Stamp）解码时间
        */
        //没有显示时间（比如未解码的 H.264 ）
        if (pkt.pts == AV_NOPTS_VALUE) {
            //AVRational time_base：时基。通过该值可以把PTS，DTS转化为真正的时间。
            AVRational time_base1 = ictx->streams[videoindex]->time_base;

            //计算两帧之间的时间
            /*
            r_frame_rate 基流帧速率  （不是太懂）
            av_q2d 转化为double类型
            */
            int64_t calc_duration = (int64_t) ((double)AV_TIME_BASE / av_q2d(ictx->streams[videoindex]->r_frame_rate));

            //配置参数
            pkt.pts = (int64_t) ((double)(frame_index * calc_duration) / (double)(av_q2d(time_base1) * AV_TIME_BASE));
            pkt.dts = pkt.pts;
            pkt.duration = (int) ((double)calc_duration / (double)(av_q2d(time_base1) * AV_TIME_BASE));
        }

        //延时
        if (pkt.stream_index == videoindex) {
            AVRational time_base = ictx->streams[videoindex]->time_base;
            AVRational time_base_q = { 1,AV_TIME_BASE };
            //计算视频播放时间
            int64_t pts_time = av_rescale_q(pkt.dts, time_base, time_base_q);
            //计算实际视频的播放时间
            int64_t now_time = av_gettime() - start_time;

            AVRational avr = ictx->streams[videoindex]->time_base;
            if (pts_time > now_time) {
                //睡眠一段时间（目的是让当前视频记录的播放时间与实际时间同步）
                av_usleep((unsigned int)(pts_time - now_time));
            }
        }

        in_stream = ictx->streams[pkt.stream_index];
        out_stream = octx->streams[pkt.stream_index];

        //计算延时后，重新指定时间戳
        pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt.duration = (int)av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
        //字节流的位置，-1 表示不知道字节流位置
        pkt.pos = -1;

        if (pkt.stream_index == videoindex) {
            printf("Send %8d video frames to output URL\n", frame_index);
            frame_index++;
        }

        //向输出上下文发送（向地址推送）
        ret = av_interleaved_write_frame(octx, &pkt);

        if (ret < 0) {
            printf("发送数据包出错\n");
            break;
        }

        //释放
        av_free_packet(&pkt);
    }

    end:
    //释放资源
    avformat_free_context(ictx);
    avio_close(octx->pb);
    avformat_free_context(ofmt);
}
