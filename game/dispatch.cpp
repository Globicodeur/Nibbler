#include "dispatch.hpp"

#include <unordered_map>

namespace spec {

    template <Event event, class...Args>
    static auto bind(Args... args) {
        return [=] { EventDispatcher::emit<event>(args...); };
    }

    void dispatchInput(gui::Input input) {
        using Emitter = std::function<void ()>;
        using DispatchMap = std::unordered_map<gui::Input, Emitter>;

        static const DispatchMap DISPATCH_MAP = {
            { gui::Input::Up,    bind<Event::ChangeDirection>(0ul, Up)    },
            { gui::Input::Down,  bind<Event::ChangeDirection>(0ul, Down)  },
            { gui::Input::Left,  bind<Event::ChangeDirection>(0ul, Left)  },
            { gui::Input::Right, bind<Event::ChangeDirection>(0ul, Right) },
            { gui::Input::W,     bind<Event::ChangeDirection>(1ul, Up)    },
            { gui::Input::S,     bind<Event::ChangeDirection>(1ul, Down)  },
            { gui::Input::A,     bind<Event::ChangeDirection>(1ul, Left)  },
            { gui::Input::D,     bind<Event::ChangeDirection>(1ul, Right) },
            { gui::Input::Key1,  bind<Event::ChangeGui>(0ul)              },
            { gui::Input::Key2,  bind<Event::ChangeGui>(1ul)              },
            { gui::Input::Key3,  bind<Event::ChangeGui>(2ul)              },
            { gui::Input::Exit,  EventDispatcher::emit<Event::Exit>       },
        };

        auto actionIt = DISPATCH_MAP.find(input);
        if (actionIt != DISPATCH_MAP.end())
            actionIt->second();
    }

    void dispatchMessage(const network::ClientMessage & message) {
        EventDispatcher::emit<Event::ChangeDirection>(
            message.id,
            message.direction
        );
    }

    void dispatchMessage(const network::ServerMessage & message) {
        static struct Visitor: boost::static_visitor<> {

            void operator()(audio::Sound sound) const {
                EventDispatcher::emit<Event::PlaySound>(sound);
            }

            void operator()(const gui::GameState & info) const {
                EventDispatcher::emit<Event::Draw>(info);
            }

        } visitor;

        boost::apply_visitor(visitor, message);
    }

}
