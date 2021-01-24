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
//入口  区别 控制台程序main  窗口GUI WinMain
//WINAPI 函数调用约定
//hInstance 当前程序的应用实例
//hPreInstance  前一个应用程序实例
//IpCmdLine  命令行参数
//nCmdShow 窗口显示方式  最大化/最小化
//HWND 窗口句柄类型 UINT 无符号整型 
//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


void CreateMyMenu()
{
	hRoot = CreateMenu();//根菜单用此函数创建菜单
	if (!hRoot)
		return;

	HMENU pop1 = CreatePopupMenu();//竖立的弹出菜单，通常作为另一个菜单的子菜单或右键菜单的顶级菜单
	AppendMenu(hRoot, MF_POPUP, (UINT_PTR)pop1, TEXT("操作"));//将子菜单添加到根菜单中
	// 一种方法是使用AppendMenu函数
	HMENU pop1_1 = CreatePopupMenu();
	AppendMenu(pop1, MF_STRING, (UINT_PTR)100, TEXT("简单3*3"));
	AppendMenu(pop1, MF_STRING, (UINT_PTR)101, TEXT("普通4*4"));
	AppendMenu(pop1, MF_STRING, (UINT_PTR)102, TEXT("困难5*5"));
	// 另一种方法是使用InsertMenuItem函数
#if 0
	HMENU pop1_2 = CreatePopupMenu();
	MENUITEMINFO mif;
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.cch = 100;
	mif.dwItemData = NULL;
	mif.dwTypeData = TEXT("机关枪");
	mif.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	mif.fState = MFS_ENABLED;
	mif.fType = MIIM_STRING;
	mif.wID = (UINT_PTR)pop1_2;

	InsertMenuItem(pop1, (UINT_PTR)pop1_2, FALSE, &mif);
#endif

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR IpCmdLine, int nCmdShow){
	//1、做一个窗口  设计窗口类；注册窗口类；创建窗口；显示窗口；更新窗口；消息循环
	//设计
	TCHAR szAppClassName[] = TEXT("软件设计");


	WNDCLASS wc;
	wc.cbClsExtra = 0;										//窗口类扩展空间大小 默认给0字节
	wc.cbWndExtra = 0;										//窗口类扩展空间大小 默认给0字节
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //加载白色背景
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				//加载光标
	wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);;	//加载图标
	wc.hInstance = hInstance;								//应用程序实例句柄
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = szAppClassName;						//窗口类型名
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;						//窗口类风格

	//注册
	RegisterClass(&wc);

	CreateMyMenu();
	//创建窗口
	HWND hWnd = CreateWindow(
		szAppClassName,  //窗口类型名
		TEXT("别踩白块"),  //窗口标题
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,  //窗口风格
		500, 200, //窗口左上角坐标
		4 * K + 17, 4 * K + 40,  //窗口宽和高
		NULL,  //父窗口句柄
		hRoot,  //菜单句柄
		hInstance,  //应用程序实例句柄
		NULL   //参数
		);

	//显示
	ShowWindow(hWnd, SW_SHOW);

	//更新
	UpdateWindow(hWnd);

	//消息循环
	MSG msg;//消息机制驱动运行
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//将虚拟键消息转换成字符消息
		TranslateMessage(&msg);
		//将消息分发给窗口处理函数
		DispatchMessage(&msg);
	}

	return 0;
}

//窗口处理函数
int InitDrawWIndows(HWND hWnd) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	InvalidateRect(hWnd, &rect, TRUE);
	return 0;
}int* bw = NULL;  //每一屏幕有四个黑块  从上到下  左到右
void InitMap() {


	bw = new int[WDITH];
	srand((unsigned)time(NULL));
	for (int i = 0; i < WDITH; i++) {
		bw[i] = rand() % WDITH;
	}
	//开启定时器
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	PAINTSTRUCT ps;
	HDC hDC;  //绘图句柄  DC 设备上下文

	RECT rect;   //矩形区域
	HBRUSH hBrush;//刷子
	POINT point;   //鼠标点击坐标
	static int count = 0;  //统计格子个数
	static int tm = 0;  //所耗时间
	TCHAR szMes[200];

	switch (uMsg)
	{
	case WM_CREATE://窗口创建时 生成随机位置  显示黑块
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
	case WM_PAINT://窗口绘制
		hDC = BeginPaint(hWnd, &ps);
		//画图Rectangle(hDC, 0, 0, 100, 100);
		//划线
		//水平
		for (int i = 0; i <= WDITH; i++){
			MoveToEx(hDC, 0, i*BLOCK, NULL);
			LineTo(hDC, 400, i*BLOCK);
		}
		//竖直
		for (int i = 0; i <= HIGH; i++){
			MoveToEx(hDC, i*BLOCK, 0, NULL);
			LineTo(hDC, i*BLOCK, HIGH * BLOCK);
		}
		//画黑块
		for (int i = 0; i < HIGH; i++){
			SetRect(&rect, bw[i] * BLOCK, i*BLOCK, bw[i] * BLOCK + BLOCK, i*BLOCK + BLOCK);
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hDC, hBrush);
			Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
			//释放资源
			DeleteObject(hBrush);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:  //左键按下
	{
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		//判断是否踩中位置
		if ((point.x / BLOCK) != bw[HIGH - 1] || point.y / BLOCK != HIGH - 1){
			wsprintf(szMes, L"您输了！用时：%d.%d秒 格数%d个，平均速度为%d", tm / 100, tm - (tm / 100) * 100, count,count*100/tm);
			MessageBox(hWnd, szMes, L"游戏结束", MB_OK);
			PostQuitMessage(0);
		}
		else if (point.y / BLOCK == HIGH - 1){
			//随机数
			for (int i = HIGH - 1; i >= 1; i--){
				bw[i] = bw[i - 1];
			}
			bw[0] = rand() % HIGH;
			count++;
			//滚动窗口  一次往下一百像素（也就是一行)
			ScrollWindow(hWnd, 0, BLOCK, NULL, NULL);
		}
	}

		break;
		//case WM_KEYDOWN:   //键盘按下
		//	break;
	case WM_CLOSE: //窗口关闭消息
		DestroyWindow(hWnd);  //销毁窗口  无法恢复
		break;
	case WM_DESTROY:  //窗口销毁消息
		PostQuitMessage(0); //退出进程
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}