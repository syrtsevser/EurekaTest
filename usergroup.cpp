#include <nan.h>

#include <windows.h>
#include <stdio.h>
#include <lm.h>

#include <lmaccess.h>
#include <lmapibuf.h>

#include <locale>
#include <codecvt>

#pragma comment(lib, "netapi32.lib")

void gCheck(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	v8::String::Utf8Value param(info[0]->ToString());
	std::string input = std::string(*param);
	std::string result = u8"����� ������ ���.";
	
	LOCALGROUP_INFO_0 *l_info;
	DWORD read, total;
	
	NetLocalGroupEnum(NULL,
		0,
		(unsigned char **)&l_info,
		MAX_PREFERRED_LENGTH,
		&read,
		&total,
		NULL);
	/*
	for (int i = 0; i<read; i++) {
		std::string tmp = l_info[1].lgrpi0_name;
		info.GetReturnValue().Set(Nan::New(tmp).ToLocalChecked()); 
	}
	*/
	
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	
	for (int i = 0; i<read; i++) {
		std::string tmp = converter.to_bytes(l_info[i].lgrpi0_name);
		if (tmp == input)
			result  = u8"������ ����.";
	}
	NetApiBufferFree(l_info);
	info.GetReturnValue().Set(Nan::New(result).ToLocalChecked()); 
}

void Init(v8::Local<v8::Object> exports) {
	exports->Set(Nan::New("usergroup_init").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(gCheck)->GetFunction());
}

NODE_MODULE(usergroup, Init)