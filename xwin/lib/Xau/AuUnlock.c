/* $Xorg: AuUnlock.c,v 1.3 2000/08/17 19:45:29 cpqbld Exp $ */

/*

Copyright 1988, 1998  The Open Group

All Rights Reserved.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/
/* $XFree86: xc/lib/Xau/AuUnlock.c,v 1.3 2001/01/17 19:42:24 dawes Exp $ */

#include <X11/Xauth.h>
#include <X11/Xos.h>

int
#if NeedFunctionPrototypes
XauUnlockAuth (
_Xconst char *file_name)
#else
XauUnlockAuth (file_name)
char	*file_name;
#endif
{
#ifndef WIN32
    char	creat_name[1025];
#endif
    char	link_name[1025];

    if (strlen (file_name) > 1022)
	return 0;
#ifndef WIN32
    (void) strcpy (creat_name, file_name);
    (void) strcat (creat_name, "-c");
#endif
    (void) strcpy (link_name, file_name);
    (void) strcat (link_name, "-l");
    /*
     * I think this is the correct order
     */
#ifndef WIN32
    (void) unlink (creat_name);
#endif
    (void) unlink (link_name);

    return 1;
}
