#include <node.h>
#include <v8.h>
#include "Windows.h"
#include "Shlobj.h"
#include <string>

using namespace v8;

void GetSystem32Path(const v8::FunctionCallbackInfo<Value>& args) {
    TCHAR szPath[MAX_PATH];
    Isolate* isolate = args.GetIsolate();

    if (FAILED(SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, 0, szPath)))
    {
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Failed to retrieve a path")));
      return;
    }

#ifdef UNICODE
    std::vector<char> buffer;
    int size = WideCharToMultiByte(CP_UTF8, 0, szPath, -1, NULL, 0, NULL, NULL);
    if (size > 0) {
        buffer.resize(size);
        WideCharToMultiByte(CP_UTF8, 0, szPath, -1, static_cast<BYTE*>(&buffer[0]), buffer.size(), NULL, NULL);
    }
    else {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Failed to convert string")));
        return
    }
    std::string string(&buffer[0]);
#else
    std::string string(szPath);
#endif

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, string.c_str()));
}

void Init(Handle<Object> exports) {
    NODE_SET_METHOD(exports, "GetSystem32Path", GetSystem32Path);
}

NODE_MODULE(hello, Init)
