#include "subtitler.h"

/*
The X character codes:
 (0)
(1)
(2)
(3)
(4)
(5)
(6)
(7)
(8)
	(9)

(10)
(11)
(12)
(13)
(14)
(15)
(16)
(17)
(18)
(19)
(20)
(21)
(22)
(23)
(24)
(25)
(26)
(27)
(28)
(29)
(30)
(31)
 (32)
!(33)
"(34)
#(35)
$(36)
%(37)
&(38)
'(39)
((40)
)(41)
*(42)
+(43)
,(44)
-(45)
.(46)
/(47)
0(48)
1(49)
2(50)
3(51)
4(52)
5(53)
6(54)
7(55)
8(56)
9(57)
:(58)
;(59)
<(60)
=(61)
>(62)
?(63)
@(64)
A(65)
B(66)
C(67)
D(68)
E(69)
F(70)
G(71)
H(72)
I(73)
J(74)
K(75)
L(76)
M(77)
N(78)
O(79)
P(80)
Q(81)
R(82)
S(83)
T(84)
U(85)
V(86)
W(87)
X(88)
Y(89)
Z(90)
[(91)
\(92)
](93)
^(94)
_(95)
`(96)
a(97)
b(98)
c(99)
d(100)
e(101)
f(102)
g(103)
h(104)
i(105)
j(106)
k(107)
l(108)
m(109)
n(110)
o(111)
p(112)
q(113)
r(114)
s(115)
t(116)
u(117)
v(118)
w(119)
x(120)
y(121)
z(122)
{(123)
|(124)
}(125)
~(126)
(127)
�(128)
�(129)
�(130)
�(131)
�(132)
�(133)
�(134)
�(135)
�(136)
�(137)
�(138)
�(139)
�(140)
�(141)
�(142)
�(143)
�(144)
�(145)
�(146)
�(147)
�(148)
�(149)
�(150)
�(151)
�(152)
�(153)
�(154)
�(155)
�(156)
�(157)
�(158)
�(159)
�(160)
�(161)
�(162)
�(163)
�(164)
�(165)
�(166)
�(167)
�(168)
�(169)
�(170)
�(171)
�(172)
�(173)
�(174)
�(175)
�(176)
�(177)
�(178)
�(179)
�(180)
�(181)
�(182)
�(183)
�(184)
�(185)
�(186)
�(187)
�(188)
�(189)
�(190)
�(191)
�(192)
�(193)
�(194)
�(195)
�(196)
�(197)
�(198)
�(199)
�(200)
�(201)
�(202)
�(203)
�(204)
�(205)
�(206)
�(207)
�(208)
�(209)
�(210)
�(211)
�(212)
�(213)
�(214)
�(215)
�(216)
�(217)
�(218)
�(219)
�(220)
�(221)
�(222)
�(223)
�(224)
�(225)
�(226)
�(227)
�(228)
�(229)
�(230)
�(231)
�(232)
�(233)
�(234)
�(235)
�(236)
�(237)
�(238)
�(239)
�(240)
�(241)
�(242)
�(243)
�(244)
�(245)
�(246)
�(247)
�(248)
�(249)
�(250)
�(251)
�(252)
�(253)
�(254)
�(255)
*/


#if 0  /* unused, except in xtputstr which is also unused --AC */
/*
This converts the xwindows code for a character to the SAA5246 Teletext chip
character set code if possible, else the original character without
accentuation is used.
*/
static int character_lookup(unsigned char char_in, int *char_out)
{
if(debug_flag)
	{
	tc_log_msg(MOD_NAME,
	"character_lookup(): arg char_in=%c(%d)",
	char_in, char_in);
	}

switch(char_in)
	{
	/* A */
	case 192: // '\'
		*char_out = 0xf1;
		break;
	case 193: // '/'
		*char_out = 0xf0;
		break;
	case 194: // '^'
		*char_out = 'A';
		return 0;
		break;
	case 195: // '~'
		*char_out = 'A';
		return 0;
		break;
	case 196: // '..'
		*char_out = 0x9b;
		break;
	/* a */
	case 224: // '\'
		*char_out = 0xea;
		break;
	case 225: // '/'
		*char_out = 0xeb;
		break;
	case 226:	// '^'
		*char_out = 0xd2;
		break;
	case 227: // '~'
		*char_out = 197;
		break;
	case 228: // '..'
		*char_out = 0x92;
		break;
	/* E */
	case 200: // '\'
		*char_out = 0xf2;
		break;
	case 201: // '/'
		*char_out = 0x90;
		break;
	case 202: // '^'
		*char_out = 'E';
		return 0;
		break;
	case 203: // '..'
		*char_out = 'E';
		return 0;
		break;
	/* e */
	case 232: // '\'
		*char_out = 0xe9;
		break;
	case 233: // '/'
		*char_out = 0xec;
		break;
	case 234: // '^'
		*char_out = 0xdc;
		break;
	case 235: // '..'
		*char_out = 0xdb;
		break;
	/* I */
	case 204: // '\'
		*char_out = 'I';
		return 0;
		break;
	case 205: // '/'
		*char_out = 0xf3;
		break;
	case 206: // '^'
		*char_out = 'I';
		return 0;
		break;
	case 207: // '..'
		*char_out = 0xf4;
		break;
	/* i */
	case 236: // '\'
		*char_out = 0xca;
		break;
	case 237: // '/'
		*char_out = 0xed;
		break;
	case 238: // '^'
		*char_out = 0xde;
		break;
	case 239: // '..'
		*char_out = 0xd4;
		break;
	/* O */
	case 210: // '\'
		*char_out = 0xf6;
		break;
	case 211: // '/'
		*char_out = 0xf5;
		break;
	case 212: // '^'
		*char_out = 'O';
		return 0;
		break;
	case 213: // '~'
		*char_out = 'O';
		return 0;
		break;
	case 214: // '..'
		*char_out = 0x9c;
		break;
	/* o */
	case 242: // '\'
		*char_out = 0xc8;
		break;
	case 243: // '/'
		*char_out = 0xee;
		break;
	case 244: // '^'
		*char_out = 0xd8;
		break;
	case 245: // '~'
		*char_out = 'o';
		return 0;
		break;
	case 246: // '..'
		*char_out = 0x98;
		break;
	/* U */
	case 217: // '\'
		*char_out = 'U';
		return 0;
		break;
	case 218: // '/'
		*char_out = 0xf7;
		break;
	case 219: // '^'
		*char_out = 'U';
		return 0;
		break;
	case 220: // '..'
		*char_out = 0x9e;
		break;
	/* u */
	case 249: // '\'
		*char_out = 0xdd;
		break;
	case 250: // '/'
		*char_out = 0xef;
		break;
	case 251: // '^'
		*char_out = 0xd9;
		break;
	case 252: // '..'
		*char_out = 0x9a;
		break;
	/* other */
	case 36: // $
		*char_out = 228;
		break;
	case 64: // @
		*char_out = 128;
		break;
	case 34: // "
		*char_out = 162;
		break;
	case 37: // %
		*char_out = 165;
		break;
	case 39: // '
		*char_out = 167;
		break;
	case 209 : // N~ capital N as in manana
		*char_out = 231;
		break;
	case 241: // n~ lower case n as in manana
		*char_out = 232;
		break;
	case 47: // /
		*char_out = 175;
		break;
	case 231: // c, lower case c as in French garcon
		*char_out = 218;
		break;
	case 199: // C, capital C as in French garcon
		*char_out = 215;
		break;
	default:
		*char_out = char_in;
		break;
	} /* end switch char_in */

return 1;
} /* end function character_lookup */
#endif /* 0 */



#if 0  /* unused --AC */
/*
converts any special codes (above 127) in X to SAA5246 special characters
if possible.
*/
static int xtputstr(int x, int y, int m, char s[])
{
char temp[2046];
int c;
char *ptr;
int i;

if(debug_flag)
	{
	tc_log_msg(MOD_NAME,
	"xtpustr(): arg x=%d y=%d m=%d s=%s",
	x, y, m, s);
	}

/* argument check */
if(! s) return 0;

/* convert characters in string to txt characters */
i = 0;
ptr = s;
while(1)
	{
	if(! character_lookup(*ptr, &c) ) {}
								/* if not translate char, no action */
	temp[i] = c;
	if(c == 0) break;

	ptr++;
	i++;
	}

//if(! tputstr(x, y, m, temp) ) return 0;

return 1;
} /* end function xtputstr */
#endif /* 0 */


int get_h_pixels(int c, font_desc_t *pfd)
{
int pixels;

if(debug_flag)
	{
	tc_log_msg(MOD_NAME, "get_h_pixels(): arg c=%c pfd=%p", c, pfd);
	}

if(c < 0) c += 256;

/* control characters */
if(c < 0x20) return 0;

pixels = pfd -> width[c] + pfd -> charspace;

//tc_log_msg(MOD_NAME, "WAS get_h_pixels(): pfd->charspace=%d subtitle_extra_character_space=%.2f",
//pfd -> charspace, subtitle_extra_character_space);

pixels += subtitle_extra_character_space;

return pixels;
} /* end function get_h_pixels */


char *p_reformat_text(char *text, int max_pixels, font_desc_t *pfd)
{
/*
wraps lines using space, if no space break in word.
if '\' found, replace it by a \n.
*/
int a, c, i;
char *textptr;
char *last_spaceptr;
char *new_text;
char *endptr;
int h_pixels;
int last_space_pixels;
int line[MAX_SCREEN_LINES];
int line_count;
double da;
int old_lines;
char *old_text;
int formatted_text_flag;
int have_old_text_flag;
int max_text_len;

if(debug_flag)
	{
	tc_log_msg(MOD_NAME, "p_reformat_text(): arg text=%s", text);
	tc_log_msg(MOD_NAME, "max_pixels=%d pfd->width['a']=%d",
	max_pixels, pfd->width['a']);
	}

//tc_log_msg(MOD_NAME, "WAS strlen(text)=%d", strlen(text) );

if(! text) return 0;

/* in never more then this space needed */
max_text_len = strlen(text) * 2 + 1;

new_text = malloc(max_text_len);
if(! new_text) return 0;

old_text = malloc(max_text_len);
if(! old_text) return 0;

/* main iteration loop */
have_old_text_flag = 0;
formatted_text_flag = 0;
old_lines = -1;
while(1)
	{
	/* clear line length memory */
	for(i = 0; i < MAX_SCREEN_LINES; i++)
		{
		line[i] = 0;
		}

	/* copy text to work space */
	strlcpy(new_text, text, max_text_len);

	/* reformat text (all of it, from the start) */
	line_count = 0;
	textptr = new_text;
	last_spaceptr = 0;
	last_space_pixels = 0;
	h_pixels = 0;
	/* for al characters */
	while(1)
		{
		if(*textptr == 0)
			{
			/* store length of this line */
			line[line_count] = h_pixels;
			line_count++;

			break;
			}

		/* have a character */
		h_pixels += get_h_pixels(*textptr, pfd);

		/* test for too long */
		if(h_pixels >= max_pixels)
			{
			if(last_spaceptr) /* break line at space */
				{
				*last_spaceptr = '\n';
				last_spaceptr = 0;

				h_pixels -= last_space_pixels;

				/* store length of this line */
				line[line_count] = last_space_pixels;
				line_count++;
				}
			else	/*
					cannot break line, no space found, break in word,
					alert user
					*/
				{
				/* first move back so we get below max_pixels */
				while(1)
					{
					/* test for past beginning of text */
					if(textptr <= new_text) break;

					/* test if before max_pixels */
					if(h_pixels <= max_pixels) break;

					/* test if some space anyways */
					if(*textptr == ' ') break;

					/* substract size character in pixels */
					h_pixels -= get_h_pixels(*textptr, pfd);

					/* move one character back */
					textptr--;
					}

				/* store length of this line */
				line[line_count] = h_pixels;
				line_count++;

				/* save char at this position */
				a = *textptr;

				/* copy up */
				/* find end text */
				endptr = textptr;
				while(1)
					{
					endptr++;
					if(*endptr == 0) break;
					}

				/* endptr now points to string termination */
				while(1)
					{
					c = *(endptr);
					*(endptr + 1) = c;

					endptr--;

					if(endptr == textptr) break;
					}

				/* put a lf in the freed space */
				*textptr = '\n';
				textptr++;

				/* restore character */
				*textptr = a;

				last_space_pixels = 0;

				h_pixels = get_h_pixels(*textptr, pfd);
				} /* end else could not break line at space */

			} /* end if wrap */
		else /* before max_pixels */
			{
			if(*textptr == ' ')
				{
				last_spaceptr = textptr;
				last_space_pixels = h_pixels;
				}

			/* also accept '\' character as an end of line */
			if( *textptr == '\\')
				{
				formatted_text_flag = 1;
				*textptr = '\n';
				}

			if(*textptr == '\n')
				{
				last_spaceptr = 0;
				last_space_pixels = 0;

				/* store length of this line */
				line[line_count] = h_pixels;
				line_count++;

				h_pixels = 0;
				}
			else
				{
				}
			} /* end else if before max_pixels */

		textptr++;
		}/* end while all characters in text */

	/* in case the text was already formatted ('\'), we leave it as is */
	if(formatted_text_flag)
		{
		free(old_text);

		return new_text;
		}

	/*
	now that the text is reformatted, check the length of the last line,
	it may contain only >one< word (in some cases).
	Since we want all lines to have about an equal length, reduce the
	available space for a line and repeat, until the last line is longer
	then the previous ones, then use the format just before that.
	*/
	if(debug_flag)
		{
		tc_log_msg(MOD_NAME,
		"p_reformat_text(): line_count=%d max_pixels=%d",
		line_count, max_pixels);
		}

	/* if only one line, ready */
	if(line_count <= 1) return new_text;

	/* test if last line length < reference length */
	a = line[line_count - 1];

	/* length preceeding line */
	da = line[line_count - 2];

	/*
	if last line longer then length preceeding return the last that was
	shorter
	*/
	if(a > da)
		{
		if(have_old_text_flag)
			{
			free(new_text);

			return old_text;
			}
		else
			{
			free(old_text);

			return new_text;
			}
		}

	/* if more lines needed, do not allow, move back */
	if(old_lines != -1)
		{
		if(line_count > old_lines)
			{
			if(have_old_text_flag)
				{
				free(new_text);

				return old_text;
				}
			else
				{
				free(old_text);

				return new_text;
				}
			}
		}

	old_lines = line_count;
	strlcpy(old_text, new_text, max_text_len);
	have_old_text_flag = 1;

	/* reduce available space */
	max_pixels--;
	if(max_pixels <= 0)
		{
		/* cannot reformat to spec */
		tc_log_warn(MOD_NAME,
"subtitler(): p_reformat_text(): cannot reformat to spec, ignoring line");

		free(new_text);
		free(old_text);

		/* return error */
		return 0;
		}

	/*
	iterate:
	try re-formatting all of the text in a smaller horizontal space.
	*/
	if(debug_flag)
		{
		tc_log_msg(MOD_NAME, "p_reformat_text(): iterating");
		}

	} /* end while iteration loop */

/* never here */
}/* end function p_reformat_text */


int p_center_text(char *text, font_desc_t *pfd)
{
/*
centers lines in the available space,
taking in to account teletext ctrl characters.
*/
int c;
char temp[1024];
char *ptr;
int line_cnt;
int free_pixels;
int lead_pixels;

if(debug_flag)
	{
	tc_log_msg(MOD_NAME,
	"p_center_text(): arg text=%s pfd->name=%s",
	text, pfd->name);
	}

line_cnt = 0;
ptr = text;
while(1) /* for all lines in text */
	{
	/* read a line to temp */
	free_pixels = line_h_end - line_h_start;
//TEXT_END - LEFT_MARGIN;
	while(1)/* for all characters in a line */
		{
		c = *ptr;

		/* detect end of text */
		if(c == 0) break;

		/* detect end of line */
		if(c == '\n') break;

		/* calculate free space in line */
		free_pixels -= get_h_pixels(c, pfd);
		if(free_pixels < 0) free_pixels = 0;

		/* next position in text */
		ptr++;
		} /* end while all characters in a line */

	/* calculate space before text */
	lead_pixels = free_pixels / 2.0;

	if(debug_flag)
		{
		tc_log_msg(MOD_NAME,
		"p_center_text(): text=%s\n"
		"free_pixels=%d lead_pixels=%d\n"
		"line_cnt=%d",
		temp,
		free_pixels, lead_pixels,
		line_cnt);
		}

	screen_start[line_cnt] = line_h_start + lead_pixels;
//LEFT_MARGIN + lead_pixels;

	/* ready if end of text */
	if(c == 0) break;

	line_cnt++;

	/* point past LF */
	ptr++;
	} /* en while all lines in text */

return 1;
} /* end function p_center text */


