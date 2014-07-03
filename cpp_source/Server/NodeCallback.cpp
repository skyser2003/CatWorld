#include "stdafx.h"
#include "NodeCallback.h"

void NodeCallback::Init(std::function<void(void)> callback)
{
	this->callback = callback;
	watcher.data = this;
	uv_async_init(uv_default_loop(), &watcher, listener);
}

void NodeCallback::Send()
{
	uv_async_send(&watcher);
}

void NodeCallback::Destroy()
{
	uv_close((uv_handle_t*)&watcher, close);
}

void NodeCallback::listener(uv_async_t* handle, int status)
{
	auto* callback = static_cast<NodeCallback*>(handle->data);
	if (callback->callback)
	{
		callback->callback();
	}

	callback->Destroy();
}

void NodeCallback::close(uv_handle_t* handle) {
	auto* callback = static_cast<NodeCallback*>(handle->data);
	delete callback;
}