#include "Input.h"

void Input::Initialize()
{
	//�L�[�{�[�h������
	keybord.Initialize();

	//�R���g���[���[������
	controller.InitController();

	//�}�E�X������
	mouse.Init();
}

void Input::Update()
{
	//�L�[�{�[�h�X�V	
	keybord.Update();
	//�R���g���[���[�X�V
	controller.UpdateInput();
	//�}�E�X�X�V
	mouse.Update();
}


bool Input::KeybordPush(BYTE keyNumber)
{
	return keybord.PushKey(keyNumber);
}

bool Input::KeybordTrigger(BYTE keyNumber)
{
	return keybord.TriggerKey(keyNumber);
}

bool Input::ControllerPush(ButtonKind button)
{
	return controller.IsButtonPush(button);
}

bool Input::ControllerUp(ButtonKind button)
{
	return controller.IsButtonUp(button);
}

bool Input::ControllerDown(ButtonKind button)
{
	return controller.IsButtonDown(button);
}

float Input::GetLeftAngle()
{
	return controller.GetLeftAngle();
}

float Input::GetRightAngle()
{
	return controller.GetRightAngle();
}

bool Input::MousePushLeft()
{
	return mouse.PushMouseLeft();
}

bool Input::MousePushMiddle()
{
	return mouse.PushMouseMiddle();
}

bool Input::MouseTriggerLeft()
{
	return mouse.TriggerMouseLeft();
}

bool Input::MouseTriggerMiddle()
{
	return mouse.TriggerMouseMiddle();
}

Mouse::MouseMove Input::GetMouseMove()
{
	return mouse.GetMouseMove();
}

