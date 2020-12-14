#include <Box2D/include/box2d.h>
#include <iostream>

using namespace std;

class MyContactListener : public b2ContactListener
{
    bool longBoolean;
    void BeginContact(b2Contact* contact)
    {

        b2Fixture* f1 = contact->GetFixtureA();
        b2Fixture* f2 = contact->GetFixtureB();

        b2FixtureUserData o1 = f1->GetUserData();
        b2FixtureUserData o2 = f2->GetUserData();
   
        longBoolean = (o1.pointer == 10 && o2.pointer == 5) || (o1.pointer == 10 && o2.pointer == 1) || (o1.pointer == 10) && (o2.pointer == 2) || (o1.pointer == 10) && (o2.pointer == 3);

        if (longBoolean)
        {
            onAir = false;
            cout << "Ground touched" << endl;
        }
    }

    void EndContact(b2Contact* contact)
    {
        b2Fixture* f1 = contact->GetFixtureA();
        b2Fixture* f2 = contact->GetFixtureB();

        b2FixtureUserData o1 = f1->GetUserData();
        b2FixtureUserData o2 = f2->GetUserData();

        longBoolean = (o1.pointer == 10 && o2.pointer == 5) || (o1.pointer == 10 && o2.pointer == 1) || (o1.pointer == 10) && (o2.pointer == 2) || (o1.pointer == 10) && (o2.pointer == 3);

        if (longBoolean)
        {
            onAir = true;
            cout << "Ground left" << endl;
        }

    }

public:
    bool onAir = false;
};
