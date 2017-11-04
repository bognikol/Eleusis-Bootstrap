// Windows header; it is not needed to include Windows headers anywhere except in main
#include "Windows.h"

// Eleusis headers
#include "Application.h"
#include "Window.h"
#include "Shape.h"
#include "SelectEdit.h"

// Note:
// Unfortunately, currently Eleusis passes STL objects through library boundry.
// It means that exact platform-configuration match of Eleusis dll needs to be used.

using namespace Eleusis;

class SampleWindow :
    public Window
{
public:
    SampleWindow()
    {
        // Let's add some content

        // Add background; otherwise background will be black
        Eleusis::Rectangle* l_background = new Eleusis::Rectangle(100._FPs, 100._FPs);
        l_background->fillColor_set(Colors::White);
        insertChild(l_background);

        // SelectEdit is a text widget which allow text selection and editing
        SelectEdit* l_se = new SelectEdit();
        l_se->height_set(200);
        l_se->width_set(200);
        l_se->setText("Edit me and then click orange circle!");
        l_se->LayoutGuest.Classic.topLeft(20, 20);
        insertChild(l_se);

        Circle* l_circle = new Circle(30);
        l_circle->fillColor_set(Colors::OrangeRed);
        l_circle->LayoutGuest.Classic.topLeft(200, 80);
        insertChild(l_circle);

        // Let's add some interactivity
        // Be careful with lambdas and variable captures though
        l_circle->mouseClick +=
            [l_se](Node* sender, MouseEventArgs* e)
        {
            Application::nativeMsgBox(l_se->getText());
        };

        l_circle->mouseEnter +=
            [l_circle](Node* sender, MouseEventArgs* e)
        {
            l_circle->fillColor_set(Colors::RoyalBlue);
        };

        l_circle->mouseLeave +=
            [l_circle](Node* sender, MouseEventArgs* e)
        {
            l_circle->fillColor_set(Colors::OrangeRed);
        };

        Eleusis::Polygon* l_poly = new Eleusis::Polygon(50, 5);
        l_poly->fillColor_set(Colors::BurlyWood);
        l_poly->LayoutGuest.Classic.topLeft(150, 500);
        insertChild(l_poly);

        // Animaton is not too difficult either
        l_poly->mouseClick +=
            [l_poly](Node* sender, MouseEventArgs* e)
        {
            l_poly->animate()->radius.endValue(1000);
            l_poly->animate()->duration_set(5000);
            l_poly->animate()->restart();
        };
    };
};

int APIENTRY wWinMain
(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow
)
{
    Application::registerInstance();

    return 
        Application::run(new SampleWindow());
}