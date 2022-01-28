#include <gtkmm.h>

class Window final : public Gtk::Window {
public:
    Window() {
      set_title("Tuple Playground");
      set_size_request(400, 400);
      set_default_size(400, 400);
      show_all();
    }
    ~Window() { }
};

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "app.tuple.app.playground");
    Window window;
    return app->run(window);
}
