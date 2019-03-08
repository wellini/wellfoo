#include "b3d_file.h"

CFStringRef StringToCF(const melange::String &in);
void	CFToString(const CFStringRef in, melange::String *out);
melange::String CFToString(CFStringRef in);
