#pragma once
class cIScene
{
private:
	
public:
	cIScene();
	virtual ~cIScene();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void EnterScene() = 0;
	virtual void ExitScene() = 0;
	virtual void ChangeScene(cIScene*) = 0;
};
