#define assignActionEx(x,CAP,CODE) x.setAction([CAP](context& arg, scene_object* src) mutable CODE);
#define assignAction(x,CODE) x.setAction([&](context& arg, scene_object* src)CODE);
#define getActionSrc(type) ((type*)src)
#define getActionParent(type) ((type*)(src->getParent()))
#define defineAction(CODE) ([&](context& arg, scene_object* src) mutable CODE)

//typedef void( *action )( context& arg, scene_object* source );

typedef std::function<void(context& arg, scene_object* source)> action;

void null_action__(context& arg, scene_object* src) {
	return;
}

action null_action = &null_action__;
