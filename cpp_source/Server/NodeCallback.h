#pragma once

class NodeCallback
{
public:
	void Init(std::function<void(void)> callback);
	void Send();
private:
	void Destroy();

	static void listener(uv_async_t* handle, int status);
	static void close(uv_handle_t* handle);

	uv_async_t watcher;
	std::function<void(void)> callback;
};