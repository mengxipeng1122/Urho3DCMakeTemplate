/* LucKey Productions Urho3D Project Template
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
*/

#include "inputmaster.h"
#include "templatecam.h"

InputMaster::InputMaster(Context* context, MasterControl* masterControl) : Object(context),
    masterControl_{masterControl},
    input_{GetSubsystem<Input>()}
{
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(InputMaster, HandleMouseButtonDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(InputMaster, HandleMouseButtonUp));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(InputMaster, HandleKeyDown));
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(InputMaster, HandleKeyUp));
    SubscribeToEvent(E_JOYSTICKBUTTONDOWN, URHO3D_HANDLER(InputMaster, HandleJoystickButtonDown));
    SubscribeToEvent(E_JOYSTICKBUTTONUP, URHO3D_HANDLER(InputMaster, HandleJoystickButtonUp));
}

void InputMaster::HandleKeyDown(StringHash eventType, VariantMap &eventData)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();
    pressedKeys_.Insert(key);

    switch (key){
        //Exit when ESC is pressed
    case KEY_ESCAPE:{
        masterControl_->Exit();
    } break;
        //Take screenshot
    case KEY_9:{
        Graphics* graphics = GetSubsystem<Graphics>();
        Image screenshot(context_);
        graphics->TakeScreenShot(screenshot);
        //Here we save in the Data folder with date and time appended
        String fileName = GetSubsystem<FileSystem>()->GetProgramDir() + "Screenshots/Screenshot_" +
                Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_')+".png";
        Log::Write(1, fileName);
        screenshot.SavePNG(fileName);
    } break;
    default: break;
    }
}
void InputMaster::HandleKeyUp(StringHash eventType, VariantMap &eventData)
{
    using namespace KeyUp;
    int key = eventData[P_KEY].GetInt();
    if (pressedKeys_.Contains(key)) pressedKeys_.Erase(key);
}

void InputMaster::HandleMouseButtonDown(StringHash eventType, VariantMap &eventData)
{
    using namespace MouseButtonDown;
    int button = eventData[P_BUTTON].GetInt();
    pressedMouseButtons_.Insert(button);
}


void InputMaster::HandleMouseButtonUp(StringHash eventType, VariantMap &eventData)
{
    using namespace MouseButtonUp;
    int button = eventData[P_BUTTON].GetInt();
    if (pressedMouseButtons_.Contains(button)) pressedMouseButtons_.Erase(button);
}

void InputMaster::HandleJoystickButtonDown(StringHash eventType, VariantMap &eventData)
{
    using namespace JoystickButtonDown;
    int joystickId = eventData[P_JOYSTICKID].GetInt();
    int button = eventData[P_BUTTON].GetInt();
    pressedJoystickButtons_.Insert(button);
}

void InputMaster::HandleJoystickButtonUp(StringHash eventType, VariantMap &eventData)
{
    using namespace JoystickButtonUp;
    int joystickId = eventData[P_JOYSTICKID].GetInt();
    int button = eventData[P_BUTTON].GetInt();
    if (pressedJoystickButtons_.Contains(button)) pressedJoystickButtons_.Erase(button);
}
