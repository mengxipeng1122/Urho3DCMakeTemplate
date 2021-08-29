/*
// Copyright (C) 2015 LucKey Productions (luckeyproductions.nl)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "luckey.h"

float LucKey::Distance(const Vector3 from, const Vector3 to){
    return (to - from).Length();
}

unsigned LucKey::IntVector2ToHash(IntVector2 vec) { return (MakeHash(vec.x_) & 0xffff) | (MakeHash(vec.y_) << 16); }

Vector3 LucKey::Scale(const Vector3 lhs, const Vector3 rhs) {
    return Vector3(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_);
}

Urho3D::IntVector2 LucKey::Scale(const Urho3D::IntVector2 lhs, const Urho3D::IntVector2 rhs) {
    return Urho3D::IntVector2(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
}

Vector2 LucKey::Rotate(const Vector2 vec2, const float angle){
    float x = vec2.x_;
    float y = vec2.y_;

    float theta = M_DEGTORAD * angle;

    float cs = cos(theta);
    float sn = sin(theta);

    return Vector2(x * cs - y * sn, x * sn + y * cs);
}

float LucKey::RandomSign()
{
    return Random(2)*2-1;
}

Color LucKey::RandomHairColor()
{
    Color hairColor{};
    hairColor.FromHSV(Random(0.1666f), Random(0.05f, 0.7f), Random(0.9f));
    return hairColor;
}

Color LucKey::RandomSkinColor()
{
    Color skinColor{};
    skinColor.FromHSV(Random(0.05f, 0.18f), Random(0.5f, 0.75f), Random(0.23f, 0.8f));
    return skinColor;
}
Color LucKey::RandomColor()
{
    Color color{};
    color.FromHSV(Random(), Random(), Random());
    return color;
}
