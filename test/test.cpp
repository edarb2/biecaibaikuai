#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include"resource.h"

#define  K   100
#define   N 	5

HMENU hRoot = NULL;
int BLOCK = 100;
int BLOCKY = 100;
int WDITH = 3;
int HIGH = 3;
//���  ���� ����̨����main  ����GUI WinMain
//WINAPI ��������Լ��
//hInstance ��ǰ�����Ӧ��ʵ��
//hPreInstance  ǰһ��Ӧ�ó���ʵ��
//IpCmdLine  �����в���
//nCmdShow ������ʾ��ʽ  ���/��С��
//HWND ���ھ������ UINT �޷������� 
//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


void CreateMyMenu()
{
	hRoot = CreateMenu();//���˵��ô˺��������˵�
	if (!hRoot)
		return;

	HMENU pop1 = CreatePopupMenu();//�����ĵ����˵���ͨ����Ϊ��һ���˵����Ӳ˵����Ҽ��˵��Ķ����˵�
	AppendMenu(hRoot, MF_POPUP, (UINT_PTR)pop1, TEXT("����"));//���Ӳ˵���ӵ����˵���
	// һ�ַ�����ʹ��AppendMenu����
	HMENU pop1_1 = CreatePopupMenu();
	AppendMenu(pop1, MF_STRING, (UINT_PTR)100, TEXT("��3*3"));
	AppendMenu(pop1, MF_STRING, (UINT_PTR)101, TEXT("��ͨ4*4"));
	AppendMenu(pop1, MF_STRING, (UINT_PTR)102, TEXT("����5*5"));
	// ��һ�ַ�����ʹ��InsertMenuItem����
#if 0
	HMENU pop1_2 = CreatePopupMenu();
	MENUITEMINFO mif;
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.cch = 100;
	mif.dwItemData = NULL;
	mif.dwTypeData = TEXT("����ǹ");
	mif.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	mif.fState = MFS_ENABLED;
	mif.fType = MIIM_STRING;
	mif.wID = (UINT_PTR)pop1_2;

	InsertMenuItem(pop1, (UINT_PTR)pop1_2, FALSE, &mif);
#endif

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR IpCmdLine, int nCmdShow){
	//1����һ������  ��ƴ����ࣻע�ᴰ���ࣻ�������ڣ���ʾ���ڣ����´��ڣ���Ϣѭ��
	//���
	TCHAR szAppClassName[] = TEXT("������");


	WNDCLASS wc;
	wc.cbClsExtra = 0;										//��������չ�ռ��С Ĭ�ϸ�0�ֽ�
	wc.cbWndExtra = 0;										//��������չ�ռ��С Ĭ�ϸ�0�ֽ�
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //���ذ�ɫ����
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				//���ع��
	wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);;	//����ͼ��
	wc.hInstance = hInstance;								//Ӧ�ó���ʵ�����
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = szAppClassName;						//����������
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;						//��������

	//ע��
	RegisterClass(&wc);

	CreateMyMenu();
	//��������
	HWND hWnd = CreateWindow(
		szAppClassName,  //����������
		TEXT("��Ȱ׿�"),  //���ڱ���
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,  //���ڷ��
		500, 200, //�������Ͻ�����
		4 * K + 17, 4 * K + 40,  //���ڿ�͸�
		NULL,  //�����ھ��
		hRoot,  //�˵����
		hInstance,  //Ӧ�ó���ʵ�����
		NULL   //����
		);

	//��ʾ
	ShowWindow(hWnd, SW_SHOW);

	//����
	UpdateWindow(hWnd);

	//��Ϣѭ��
	MSG msg;//��Ϣ������������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//���������Ϣת�����ַ���Ϣ
		TranslateMessage(&msg);
		//����Ϣ�ַ������ڴ�����
		DispatchMessage(&msg);
	}

	return 0;
}

//���ڴ�����
int InitDrawWIndows(HWND hWnd) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	InvalidateRect(hWnd, &rect, TRUE);
	return 0;
}int* bw = NULL;  //ÿһ��Ļ���ĸ��ڿ�  ���ϵ���  ����
void InitMap() {


	bw = new int[WDITH];
	srand((unsigned)time(NULL));
	for (int i = 0; i < WDITH; i++) {
		bw[i] = rand() % WDITH;
	}
	//������ʱ��
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	PAINTSTRUCT ps;
	HDC hDC;  //��ͼ���  DC �豸������

	RECT rect;   //��������
	HBRUSH hBrush;//ˢ��
	POINT point;   //���������
	static int count = 0;  //ͳ�Ƹ��Ӹ���
	static int tm = 0;  //����ʱ��
	TCHAR szMes[200];

	switch (uMsg)
	{
	case WM_CREATE://���ڴ���ʱ �������λ��  ��ʾ�ڿ�
	{
		WDITH = 4;
		HIGH = 4;
		BLOCK = (4 * K) / 4;
		BLOCKY = (4 * K) / 4;

		InitMap();

		SetTimer(hWnd, 1, 10, NULL);

	}
		break;
	case WM_TIMER:
		tm++;
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case 100:
		{
			WDITH = 3;
			HIGH = 3;

			BLOCK = (4 * K) / 3;
			BLOCKY = (4 * K) / 3;
			InitMap();
			InitDrawWIndows(hWnd);
		}
			break;
		case 101: {
			WDITH = 4;
			HIGH = 4;
			BLOCK = (4 * K) / 4;
			BLOCKY = (4 * K) / 5;
			InitMap();
			InitDrawWIndows(hWnd);
		}
			break;
		case 102: {
			WDITH = 5;
			HIGH = 5;
			BLOCK = (4 * K) / 5;
			BLOCKY = (4 * K) / 5;
			InitMap();
			InitDrawWIndows(hWnd);
		}
			break;
		}
	}
		break;
	case WM_PAINT://���ڻ���
		hDC = BeginPaint(hWnd, &ps);
		//��ͼRectangle(hDC, 0, 0, 100, 100);
		//����
		//ˮƽ
		for (int i = 0; i <= WDITH; i++){
			MoveToEx(hDC, 0, i*BLOCK, NULL);
			LineTo(hDC, 400, i*BLOCK);
		}
		//��ֱ
		for (int i = 0; i <= HIGH; i++){
			MoveToEx(hDC, i*BLOCK, 0, NULL);
			LineTo(hDC, i*BLOCK, HIGH * BLOCK);
		}
		//���ڿ�
		for (int i = 0; i < HIGH; i++){
			SetRect(&rect, bw[i] * BLOCK, i*BLOCK, bw[i] * BLOCK + BLOCK, i*BLOCK + BLOCK);
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hDC, hBrush);
			Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
			//�ͷ���Դ
			DeleteObject(hBrush);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:  //�������
	{
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		//�ж��Ƿ����λ��
		if ((point.x / BLOCK) != bw[HIGH - 1] || point.y / BLOCK != HIGH - 1){
			wsprintf(szMes, L"�����ˣ���ʱ��%d.%d�� ����%d����ƽ���ٶ�Ϊ%d", tm / 100, tm - (tm / 100) * 100, count,count*100/tm);
			MessageBox(hWnd, szMes, L"��Ϸ����", MB_OK);
			PostQuitMessage(0);
		}
		else if (point.y / BLOCK == HIGH - 1){
			//�����
			for (int i = HIGH - 1; i >= 1; i--){
				bw[i] = bw[i - 1];
			}
			bw[0] = rand() % HIGH;
			count++;
			//��������  һ������һ�����أ�Ҳ����һ��)
			ScrollWindow(hWnd, 0, BLOCK, NULL, NULL);
		}
	}

		break;
		//case WM_KEYDOWN:   //���̰���
		//	break;
	case WM_CLOSE: //���ڹر���Ϣ
		DestroyWindow(hWnd);  //���ٴ���  �޷��ָ�
		break;
	case WM_DESTROY:  //����������Ϣ
		PostQuitMessage(0); //�˳�����
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}