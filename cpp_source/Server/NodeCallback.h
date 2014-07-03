#pragma once

class NodeCallback
{
public:
	void Init(std::function<void(void)> callback);
	void Destroy();

	void Send();
private:
	static void listener(uv_async_t* handle, int status);
	static void close(uv_handle_t* handle);

	uv_async_t watcher;
	std::function<void(void)> callback;
};