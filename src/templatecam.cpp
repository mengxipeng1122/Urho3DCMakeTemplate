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

#include "templatecam.h"

TemplateCam::TemplateCam(Context *context, MasterControl *masterControl):
    Object(context)
{
    masterControl_ = masterControl;

    rootNode_ = masterControl_->world.scene->CreateChild("Camera");
    camera_ = rootNode_->CreateComponent<Camera>();
    camera_->SetFarClip(1024.0f);
    rootNode_->SetPosition(Vector3(0.0f, 1.0f, -13.0f));
    rootNode_->SetRotation(Quaternion(10.0f, 0.0f, 0.0f));

//    Zone* zone = rootNode_->CreateComponent<Zone>();
//    zone->SetFogStart(13.0f);
//    zone->SetFogEnd(23.0f);

    SetupViewport();
}

void TemplateCam::SetupViewport()
{
    //Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, masterControl_->world.scene, camera_));
    viewport_ = viewport;

    //Add anti-asliasing and bloom
    effectRenderPath_ = viewport_->GetRenderPath()->Clone();
    effectRenderPath_->Append(masterControl_->cache_->GetResource<XMLFile>("PostProcess/FXAA3.xml"));
    effectRenderPath_->SetEnabled("FXAA3", true);
    effectRenderPath_->Append(masterControl_->cache_->GetResource<XMLFile>("PostProcess/Bloom.xml"));
    effectRenderPath_->SetShaderParameter("BloomThreshold", 0.23f);
    effectRenderPath_->SetShaderParameter("BloomMix", Vector2(1.75f, 1.25f));
    effectRenderPath_->SetEnabled("Bloom", true);

    Renderer* renderer = GetSubsystem<Renderer>();
    viewport_->SetRenderPath(effectRenderPath_);
    renderer->SetViewport(0, viewport_);
}

Vector3 TemplateCam::GetWorldPosition()
{
    return rootNode_->GetWorldPosition();
}

Quaternion TemplateCam::GetRotation()
{
    return rootNode_->GetRotation();
}
