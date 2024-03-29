#pragma once

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
#define SAFE_DELETE(p)  if(p != nullptr){ delete p; p = nullptr;}