#pragma once
#include "graphicsmath.h"

class Transformation
{
public:
	Transformation();
	void Scale(float x, float y, float z);
	void Rotation(float x, float y, float z);
	void Position(float x, float y, float z);
	const Matrix4f* GetWorldTransformation();

private:
	Vector3f m_scale;
	Vector3f m_rotation;
	Vector3f m_position;
};

Transformation::Transformation()
{
	m_scale = Vector3f(1.f);
	m_rotation = Vector3f();
	m_position = Vector3f();
}

void Transformation::Scale(float x,float y,float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Transformation::Rotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Transformation::Position(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

const Matrix4f* Transformation::GetWorldTransformation()
{
	Matrix4f World;
	Matrix4f ScaleTransform;
	Matrix4f RotationTransform;
	Matrix4f TranslationTransform;

	ScaleTransform.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
	RotationTransform.InitRotationTransform(m_rotation.x, m_rotation.y, m_rotation.z);
	TranslationTransform.InitTranslationTransform(m_position.x, m_position.y, m_position.z);

	World = TranslationTransform * RotationTransform * ScaleTransform;
	return &World;
}