#pragma once

#define SafeDelete(x) if(x) { delete x ; x = nullptr;}


#include<Windows.h>
#include<stdio.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<time.h>
#include<string>
#include<list>
#include<map>
#include<vector>

//
#include"Singleton.h"
#include"Input.h"
#include"Application.h"
#include"Renderer.h"
#include"Transform.h"
#include"GameObject.h"
#include"Mesh.h"
#include"ObjectManager.h"
#include"Scene.h"
#include"SceneManager.h"
#include"Camera.h"