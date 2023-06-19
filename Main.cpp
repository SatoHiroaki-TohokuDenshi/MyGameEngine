//�C���N���[�h
#include <Windows.h>
#include "Direct3D.h"
#include "Camera.h"
#include "Quad.h"
#include "Dice.h"
#include "Sprite.h"

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";			//�E�B���h�E�N���X��
const char* WIN_TITLE_NAME = "�T���v���Q�[��";		//�^�C�g���o�[�̕\�����e
const int WINDOW_WIDTH = 800;		//�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600;		//�E�B���h�E�̍���

//�|���S���\���i�������j
Quad* pQuad = nullptr;
Dice* pDice = nullptr;
Sprite* pSprite = nullptr;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;          //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,      //�E�B���h�E�N���X��
		WIN_TITLE_NAME,      //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                //�E�B���h�E��
		winH,                //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr = S_OK;

	//Direct3D������
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		//�G���[����
		MessageBox(nullptr, "Direct3D�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}

	//�J�����̏�����
	Camera::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//�|���S���\���i�������j
	pQuad = new Quad;
	hr = pQuad->Initialize();
	if (FAILED(hr)) {
		//�G���[����
		MessageBox(nullptr, "�C���X�^���X\"Quad\"�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	pDice = new Dice;
	hr = pDice->Initialize();
	if (FAILED(hr)) {
		//�G���[����
		MessageBox(nullptr, "�C���X�^���X\"Dice\"�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	pSprite = new Sprite;
	hr = pSprite->Initialize();
	if (FAILED(hr)) {
		//�G���[����
		MessageBox(nullptr, "�C���X�^���X\"Dice\"�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����i�E�B���h�E�����Ȃǂ̏�����D��j
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			Camera::Update();
			//�Q�[���̏���

			//�`�揈��
			Direct3D::BeginDraw();		//�o�b�N�o�b�t�@�̏�����

			static XMMATRIX Imat = XMMatrixIdentity();
			XMMATRIX Wmat = Imat * XMMatrixRotationX(XMConvertToRadians(0.02f)) * XMMatrixRotationY(XMConvertToRadians(0.02f)) * XMMatrixRotationZ(XMConvertToRadians(0.02f));
			//pQuad->Draw(mat);
			pDice->Draw(Wmat);
			pSprite->Draw(Imat);

			Direct3D::EndDraw();		//�o�b�t�@�̓���ւ�
		}
	}

	//�������
	SAFE_RELEASE(pQuad);
	SAFE_DELETE(pQuad);
	SAFE_RELEASE(pDice);
	SAFE_DELETE(pDice);
	SAFE_RELEASE(pSprite);
	SAFE_DELETE(pSprite);
	Direct3D::Release();

	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
//�Ԃ�l�@LRESULT�i�����ȊO�ł͓��Ɏg��Ȃ�����C�ɂ��Ȃ��ă��V�j
//CALLBACK�@����̏󋵂ŌĂ΂�����Đ錾�i�ʏ�͏���ɌĂ΂ꂽ�肵�Ȃ��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// �����ŏ������`���������b�Z�[�W
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	//�f�t�H���g�̏����ł������b�Z�[�W
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

