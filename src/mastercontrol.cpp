/* LucKey Productions Urho3D Project Template

// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>
*/

#include "mastercontrol.h"
#include "templatecam.h"
#include "inputmaster.h"
#include "urho.h"

URHO3D_DEFINE_APPLICATION_MAIN(MasterControl);

MasterControl::MasterControl(Context *context):
    Application(context)
{
}

void MasterControl::Setup()
{
    engineParameters_["WindowTitle"] = "LucKey Productions Urho3D Project Template";
    engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs")+"LucKeyTemplate.log";
//    engineParameters_["FullScreen"] = false;
//    engineParameters_["WindowWidth"] = 960;
//    engineParameters_["WindowHeight"] = 540;
}
void MasterControl::Start()
{
    new InputMaster(context_, this);
    cache_ = GetSubsystem<ResourceCache>();

    CreateScene();


    //Play music
    Sound* music = cache_->GetResource<Sound>("Resources/Music/Urho - Disciples of Urho.ogg");
    music->SetLooped(true);
    Node* musicNode = world.scene->CreateChild("Music");
    SoundSource* musicSource = musicNode->CreateComponent<SoundSource>();
    musicSource->SetSoundType(SOUND_MUSIC);
    musicSource->Play(music);
}
void MasterControl::Stop()
{
    engine_->DumpResources(true);
}
void MasterControl::Exit()
{
    engine_->Exit();
}


void MasterControl::CreateScene()
{
    world.scene = new Scene(context_);
    world.scene->CreateComponent<Octree>();
    world.camera = new TemplateCam(context_, this);
    CreateLights();
    new Urho(context_, this);
}

void MasterControl::CreateLights()
{
    //Add a directional light to the world. Enable cascaded shadows on it
    Node* downardsLightNode = world.scene->CreateChild("DirectionalLight");
    downardsLightNode->SetPosition(Vector3(-2.0f, 10.0f, -5.0f));
    downardsLightNode->LookAt(Vector3(0.0f, 0.0f, 0.0f));
    Light* downwardsLight = downardsLightNode->CreateComponent<Light>();
    downwardsLight->SetLightType(LIGHT_DIRECTIONAL);
    downwardsLight->SetBrightness(0.666f);
    downwardsLight->SetColor(Color(0.8f, 0.9f, 0.95f));
    downwardsLight->SetCastShadows(true);
    downwardsLight->SetShadowIntensity(0.23f);
    downwardsLight->SetShadowBias(BiasParameters(0.000025f, 0.5f));
    downwardsLight->SetShadowCascade(CascadeParameters(1.0f, 5.0f, 23.0f, 100.0f, 0.8f));

    //Add a directional light to the world. Enable cascaded shadows on it
    Node* upwardsLightNode = world.scene->CreateChild("DirectionalLight");
    upwardsLightNode->SetPosition(Vector3(3.0f, -10.0f, -5.0f));
    upwardsLightNode->LookAt(Vector3(0.0f, 0.0f, 0.0f));
    Light* upwardsLight = upwardsLightNode->CreateComponent<Light>();
    upwardsLight->SetLightType(LIGHT_DIRECTIONAL);
    upwardsLight->SetBrightness(0.5);
    upwardsLight->SetColor(Color(0.23f, 0.666f, 1.0f));

    //Create a point light. Enable cascaded shadows on it
    Node* pointLightNode_ = world.scene->CreateChild("MovingLight");
    pointLightNode_->SetPosition(Vector3(0.0f, -1.0f, -13.0f));
    Light* pointLight = pointLightNode_->CreateComponent<Light>();
    pointLight->SetLightType(LIGHT_POINT);
    pointLight->SetBrightness(0.1f);
    pointLight->SetRange(23.0f);
    pointLight->SetColor(Color(0.5f, 1.23f, 0.75f));
}
