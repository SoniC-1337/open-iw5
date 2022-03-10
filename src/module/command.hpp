#pragma once
#include "loader/module_loader.hpp"

#include "game/structs.hpp"
#include "game/game.hpp"

#include "utils/memory.hpp"

class command final : public module
{
public:
	class params
	{
	public:
		params();

		int size() const;
		const char* get(int index) const;
		std::string join(int index) const;

		const char* operator[](const int index) const
		{
			return this->get(index);
		}

	private:
		int nesting_;
	};

	class params_sv
	{
	public:
		params_sv();

		int size() const;
		const char* get(int index) const;
		std::string join(int index) const;

		const char* operator[](const int index) const
		{
			return this->get(index);
		}

	private:
		int nesting_;
	};

	static void add(const char* name, const std::function<void(const params&)>& callback);
	static void add(const char* name, const std::function<void()>& callback);

	static void add_sv(const char* name, std::function<void(game::native::gentity_s*, const params_sv&)> callback);

	void post_load() override;
	void pre_destroy() override;

private:
	static utils::memory::allocator allocator_;

	static std::unordered_map<std::string, std::function<void(const params&)>> handlers;
	static std::unordered_map<std::string, std::function<void(game::native::gentity_s*, params_sv&)>> handlers_sv;

	static void main_handler();

	static void client_command_stub(int client_num);
	static void client_command_dedi_stub();

	static void add_raw(const char* name, void (*callback)());
};
