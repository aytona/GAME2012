#pragma once

#include "graphicsmath.h"

class Transform
{
public:
	Transform();
	void Scale(float x, float y, float z);
	void Position(float x, float y, float z);
	void Rotation(float x, float y, float z);
	const Matrix4f* GetWorldTransform();

private:
	Vector3f m_scale;
	Vector3f m_position;
	Vector3f m_rotation;

	Matrix4f m_worldTransformation;
};

Transform::Transform()
{
	m_scale = Vector3f(1.0f);
	m_position = Vector3f();
	m_rotation = Vector3f();
}

void Transform::Scale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Transform::Position(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Transform::Rotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

const Matrix4f* Transform::GetWorldTransform()
{
	Matrix4f ScaleTransform;
	Matrix4f RotationTransform;
	Matrix4f PositionTransform;

	ScaleTransform.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
	RotationTransform.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);
	PositionTransform.InitTranslationTransform(m_position.x, m_position.y, m_position.z);

	m_worldTransformation = PositionTransform * RotationTransform * ScaleTransform;

	return &m_worldTransformation;
}