.\" $XConsortium: xinit.man,v 1.22 94/04/17 20:24:31 dpw Exp $
.\" $XFree86: xc/programs/xinit/xinit.man,v 3.0 1995/06/25 09:04:24 dawes Exp $
.\" Copyright (c) 1988  X Consortium
.\" 
.\" Permission is hereby granted, free of charge, to any person obtaining
.\" a copy of this software and associated documentation files (the
.\" "Software"), to deal in the Software without restriction, including
.\" without limitation the rights to use, copy, modify, merge, publish,
.\" distribute, sublicense, and/or sell copies of the Software, and to
.\" permit persons to whom the Software is furnished to do so, subject to
.\" the following conditions:
.\" 
.\" The above copyright notice and this permission notice shall be included
.\" in all copies or substantial portions of the Software.
.\" 
.\" THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
.\" OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
.\" MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
.\" IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
.\" OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
.\" ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
.\" OTHER DEALINGS IN THE SOFTWARE.
.\" 
.\" Except as contained in this notice, the name of the X Consortium shall
.\" not be used in advertising or otherwise to promote the sale, use or
.\" other dealings in this Software without prior written authorization
.\" from the X Consortium.
.TH XINIT 1 "Release 6" "X Version 11"
.SH NAME
xinit \- X Window System initializer
.SH SYNOPSIS
.B xinit
[ [
.I client
]
.I options
] [
.B \-\^\-
[
.I server
] [
.I display
]
.I options
]
.SH DESCRIPTION
The \fIxinit\fP program is used to start the X Window System server and a first
client program on systems that
cannot start X directly from \fI/etc/init\fP or in environments
that use multiple window systems.  When this first client exits, 
\fIxinit\fP will kill the X server and then terminate.
.PP
If no specific client program is given on the command line,
\fIxinit\fP will look for a file in the user's home directory
called \fI.xinitrc\fP to run as a shell script to start up client programs.
If no such file exists, \fIxinit\fP will use the following as a default:
.sp
	xterm  \-geometry  +1+1  \-n  login  \-display  :0
.sp
.PP
If no specific server program is given on the command line,
\fIxinit\fP will look for a file in the user's home directory
called \fI.xserverrc\fP to run as a shell script to start up the server.
If no such file exists, \fIxinit\fP will use the following as a default:
.sp
	X  :0
.sp
Note that this assumes that there is a program named \fIX\fP in the current
search path.  However, servers are usually named \fIXdisplaytype\fP where 
\fIdisplaytype\fP is the type of graphics display which is driven by this
server.  The site administrator should, therefore, make a link to the 
appropriate type of server on the machine, or create a shell script that
runs \fIxinit\fP with the appropriate server.
.PP
Note, when using a \fI.xserverrc\fP script be sure to ``exec'' the real X server.
Failing to do this can make the X server slow to start and exit.  For example:
.sp
	exec Xdisplaytype
.PP
An important point is that programs which are run by \fI\.xinitrc\fP
should be run in the background if they do 
not exit right away, so that they don't prevent other programs from
starting up.
However, the last long-lived program started (usually
a window manager or terminal emulator) should be
left in the foreground so that the script won't exit (which
indicates that the user is done and that \fIxinit\fP should exit).
.PP
An alternate client and/or server may be specified on the
command line.  The desired client program and its arguments should be given
as the first command line arguments to \fIxinit\fP.  To specify a particular
server command line, append a double dash (\-\^\-) to the \fIxinit\fP command
line (after any client and arguments) followed by the desired server command.
.PP
Both the client program name and the server program name must begin with a
slash (/) or a period (.).  Otherwise, they are treated as an arguments to be
appended to their respective startup lines.  This makes it possible to 
add arguments (for example, foreground and background colors) without 
having to retype the whole command line.
.PP
If an explicit server name is not given and the first argument following the
double dash (\-\^\-) is a colon followed by a digit, \fIxinit\fP will use that 
number as the display 
number instead of zero.  All remaining arguments are appended to the server 
command line.
.PP
.SH EXAMPLES
Below are several examples of how command line arguments in \fIxinit\fP are
used.
.TP 8
.B "xinit"
This will start up a server named \fIX\fP and run the user's \fI\.xinitrc\fP,
if it exists, or else start an \fIxterm\fP.
.TP 8
.B "xinit \-\^\- /usr/X11R6/bin/Xqdss  :1"
This is how one could start a specific type of server on an alternate display.
.TP 8
.B "xinit \-geometry =80x65+10+10 \-fn 8x13 \-j \-fg white \-bg navy"
This will start up a server named \fIX\fP, and will append the given
arguments to the default \fIxterm\fP command.  It will ignore \fI\.xinitrc\fP.
.TP 8
.B "xinit \-e widgets \-\^\- ./Xsun \-l \-c"
This will use the command \fI\.\/Xsun \-l \-c\fP to start the server and will
append the arguments \fI\-e widgets\fP to the default \fIxterm\fP command.
.TP 8
.B "xinit /usr/ucb/rsh fasthost cpupig \-display ws:1 \-\^\-  :1 \-a 2 \-t 5"
This will start a server named \fIX\fP on display 1 with the arguments
\fI\-a 2 \-t 5\fP.  It will then start a remote shell on the machine
\fBfasthost\fP in which it will run the command \fIcpupig\fP, telling it
to display back on the local workstation.
.PP
Below is a sample \fI\.xinitrc\fP that starts a clock, several terminals, and
leaves the window manager running as the ``last'' application.  Assuming that
the window manager has been configured properly, the user
then chooses the ``Exit'' menu item to shut down X.
.sp
.in +8
.nf
xrdb \-load $HOME/.Xresources
xsetroot \-solid gray &
xclock \-g 50x50\-0+0 \-bw 0 &
xload \-g 50x50\-50+0 \-bw 0 &
xterm \-g 80x24+0+0 &
xterm \-g 80x24+0\-0 &
twm
.fi
.in -8
.sp
Sites that want to create a common startup environment could simply create
a default \fI\.xinitrc\fP that references a site-wide startup file:
.sp
.in +8
.nf
#!/bin/sh
\&. /usr/local/lib/site.xinitrc
.fi
.in -8
.sp
Another approach is to write a script that starts \fIxinit\fP with a specific
shell script.  Such scripts are usually named \fIx11\fP, \fIxstart\fP, or
\fIstartx\fP and are a convenient way to provide a simple interface for
novice users:
.sp
.in +8
.nf
#!/bin/sh
xinit /usr/local/lib/site.xinitrc \-\^\- /usr/X11R6/bin/X bc
.fi
.in -8
.sp
.SH "ENVIRONMENT VARIABLES"
.TP 15
.B DISPLAY
This variable gets set to the name of the display to which clients should
connect.
.TP 15
.B XINITRC
This variable specifies an init file containing shell commands to start up the
initial windows.  By default, \fI\.xinitrc\fP in the home directory will be 
used.
.SH FILES
.TP 15
.I .xinitrc
default client script
.TP 15
.I xterm
client to run if \fI.xinitrc\fP does not exist
.TP 15
.I .xserverrc
default server script
.TP 15
.I X
server to run if \fI.xserverrc\fP does not exist
.SH "SEE ALSO"
.IR X (1),
.IR startx (1),
.IR Xserver (1),
.IR xterm (1)
.SH AUTHOR
Bob Scheifler, MIT Laboratory for Computer Science
