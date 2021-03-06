#pragma once
#include "Live2D.h"
#include "Live2DModelD3D.h"
#include "motion\Live2DMotion.h"
#include "motion\MotionQueueManager.h"
#include "motion\EyeBlinkMotion.h" 
#include "physics\PhysicsHair.h"
#include "L2DExpressionMotion.h"
#include <vector>

using std::vector;

typedef live2d::Live2DModelD3D Model;
typedef live2d::Live2DMotion Motion;
typedef LPDIRECT3DTEXTURE9 Texture;

class CRendererL2D : public CRenderer
{
public:
	static HRESULT Create(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, CRenderer **ppRenderer);
	~CRendererL2D();

	long AddModel(Model* model);
	Model* GetModel(long hModel);
	void RemoveModel(long hModel);

	void AddTexture(long hModel, Texture texture);
	long GetTextureCount(long hModel);

	long LoadModel(char* modelPath);
	void SetParamFloatInt(long hModel, int key, float value);
	void SetParamFloatString(long hModel, char* key, float value);
	void AddToParamFloat(long hModel, char* key, float value);
	void MultParamFloat(long hModel, char* key, float value);
	float GetParamFloatInt(long hModel, int key);
	float GetParamFloatString(long hModel, char* key);
	void SetPartsOpacityInt(long hModel, int key, float value);
	void SetPartsOpacityString(long hModel, char* key, float value);
	float GetPartsOpacityInt(long hModel, int key);
	float GetPartsOpacityString(long hModel, char* key);
	int GetParamIndex(long hModel, char* key);
	int GetPartsDataIndex(long hModel, char* key);
	void SaveParam(long hModel);
	void LoadParam(long hModel);
	HRESULT SetTexture(long hModel, LPCWSTR texturePath);

	long AddMotion(Motion* motion);
	Motion* GetMotion(long hMotion);
	void RemoveMotion(long hMotion);

	long LoadMotion(char* motionPath);
	void SetFadeIn(long hMotion, int msec);
	void SetFadeOut(long hMotion, int msec);
	void SetLoop(long hMotion, bool loop);

	void StartMotion(long hMotion);
	bool UpdateMotion(long hModel);
	bool MotionIsFinished();

	void EyeBlinkUpdate(long hModel);

	live2d::PhysicsHair* GetPhysics(long physicsHandler);
	long CRendererL2D::AddPhysics(live2d::PhysicsHair* physics);
	long CreatePhysics();
	void PhysicsSetup(long physicsHandler, float baseLengthM, float airRegistance, float mass);
	void PhysicsAddSrcParam(long physicsHandler, const char* srcType, const char * paramID, float scale, float weight);
	void PhysicsAddTargetParam(long phsyicsHandler, const char* targetType, const char* paramID, float scale, float weight);
	void PhysicsUpdate(long physicsHandler, long hModel, INT64 time);

	live2d::framework::L2DExpressionMotion* GetExpression(long expressionHandler);
	long AddExpression(live2d::framework::L2DExpressionMotion* expression);
	long CreateExpression();
	void StartExpression(long expressionHandler);
	void ExpressionSetFadeIn(long expressionHandler, int FadeInMSec);
	void ExpressionSetFadeOut(long expressionHandler, int FadeOutMSec);
	void ExpressionAddParam(long expressionHandler, char* paramID, char* calc, float value, float defaultValue);
	void ExpressionAddParamV09(long expressionHandler, char* paramID, float value, float defaultValue);
	bool UpdateExpression(long hModel);
	bool ExpressionIsFinished();

	INT64 GetUserTimeMSec();
	HRESULT BeginRender(long hModel);
	HRESULT EndRender(long hModel);
	void Dispose();

protected:
	HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter);

private:

#pragma region [   HandleVectors   ]
	vector<Model*> m_models;
	vector<vector<Texture>> m_textures;
	vector<Motion*> m_motions;
	vector<live2d::PhysicsHair*> m_physics;
	vector<live2d::framework::L2DExpressionMotion*> m_expression;
#pragma endregion

	live2d::MotionQueueManager* m_motionManager;
	live2d::MotionQueueManager* m_expressionManager;
	live2d::EyeBlinkMotion* m_eyeBlink;

	CRendererL2D();
	IDirect3DVertexBuffer9 *m_pd3dVB;
};