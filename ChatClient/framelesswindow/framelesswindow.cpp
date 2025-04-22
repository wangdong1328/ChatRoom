#include "framelesswindow.h"

FramelessWindow::FramelessWindow(QWidget* parent)
	: QWidget{ parent }
{
	this->setWindowFlags(this->windowFlags() | Qt::WindowType::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
	auto hwnd = reinterpret_cast<HWND>(this->winId());
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	SetWindowLong(hwnd, GWL_STYLE, style | WS_THICKFRAME  | WS_MINIMIZEBOX | WS_CAPTION |WS_MAXIMIZEBOX );

	const MARGINS shadow = { 1, 1, 1, 1 };
    //::DwmExtendFrameIntoClientArea(hwnd, &shadow);
}

void FramelessWindow::setTitleBar(QWidget* titleBar)
{
    if (!titleBar)
    {
        return;
    }
    this->m_titleBar = titleBar;
}

bool FramelessWindow::nativeEvent(const QByteArray& eventType, void* message, qint64* result)
{
	MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message)
    {
        case WM_NCCALCSIZE :
            {
                *result = 0;
                return true;
            }
        case WM_NCHITTEST :
            {
                long x = GET_X_LPARAM(msg->lParam);
                long y = GET_Y_LPARAM(msg->lParam);
                QPoint mouse_pos(x, y);
                *result = this->adjustResizeWindow(msg->hwnd, mouse_pos);
                if (0 != *result) return true;
                if (!this->m_titleBar) return false;
                // support highdpi
                double dpr = this->devicePixelRatioF();
                QPoint pos = m_titleBar->mapFromGlobal(QPoint(x / dpr, y / dpr));
                if (!this->m_titleBar->rect().contains(pos)) return false;
                QWidget* child = this->m_titleBar->childAt(pos);
                if (!child)
                {
                    *result = HTCAPTION;
                    return true;
                }
                return false;
            }
        // 处理其他消息
        case WM_SHOWWINDOW :
            {
                if (msg->wParam)
                {
                    // 获取窗口句柄
                    auto hwnd = reinterpret_cast<HWND>(this->winId());

                    // 获取屏幕分辨率
                    RECT rect;
                    GetWindowRect(hwnd, &rect);
                    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

                    // 计算窗口位置
                    int windowWidth = rect.right - rect.left;
                    int windowHeight = rect.bottom - rect.top;
                    int posX = (screenWidth - windowWidth) / 2;
                    int posY = (screenHeight - windowHeight) / 2;

                    // 设置窗口位置
                    SetWindowPos(hwnd, HWND_TOP, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                }
                break;
            }
        default :
            break;
    }

    return QWidget::nativeEvent(eventType, message, result);
}

bool FramelessWindow::event(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange) {
		if (this->isMaximized())
		{
			RECT frame = { 0, 0, 0, 0 };
			AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
			double dpr = this->devicePixelRatioF();
			frame.left = std::abs(frame.left / dpr);
			frame.top = std::abs(frame.bottom / dpr);
			QWidget::setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
		}
		else
        {
            QWidget::setContentsMargins(QMargins(0, 0, 0, 0));
        }
    }

    return QWidget::event(event);
}

int FramelessWindow::adjustResizeWindow(HWND hwnd, const QPoint& pos)
{
	int result = 0;

	RECT winrect;
	GetWindowRect(HWND(this->winId()), &winrect);

	int mouse_x = pos.x();
	int mouse_y = pos.y();

	bool resizeWidth = this->minimumWidth() != this->maximumWidth();
	bool resizeHieght = this->minimumHeight() != this->maximumHeight();

    if (resizeWidth)
    {
        if (mouse_x > winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH) result = HTLEFT;
        if (mouse_x < winrect.right && mouse_x >= winrect.right - RESIZE_WINDOW_WIDTH) result = HTRIGHT;
    }

    if (resizeHieght)
    {
        if (mouse_y < winrect.top + RESIZE_WINDOW_WIDTH && mouse_y >= winrect.top) result = HTTOP;
        if (mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH) result = HTBOTTOM;
    }

    if (resizeWidth && resizeHieght)
    {
        // topleft corner
        if (mouse_x >= winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH &&
            mouse_y >= winrect.top && mouse_y < winrect.top + RESIZE_WINDOW_WIDTH)
        {
            result = HTTOPLEFT;
        }

        // topRight corner
        if (mouse_x <= winrect.right && mouse_x > winrect.right - RESIZE_WINDOW_WIDTH &&
            mouse_y >= winrect.top && mouse_y < winrect.top + RESIZE_WINDOW_WIDTH)
            result = HTTOPRIGHT;

        // leftBottom  corner
        if (mouse_x >= winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH &&
            mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOMLEFT;

        // rightbottom  corner
        if (mouse_x <= winrect.right && mouse_x > winrect.right - RESIZE_WINDOW_WIDTH &&
            mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOMRIGHT;
    }

    return result;
}

FramelessWindowForDialog::FramelessWindowForDialog(QWidget* parent) :
	QDialog{ parent }
{
	this->setWindowFlags(Qt::Window);

	auto hwnd = reinterpret_cast<HWND>(this->winId());
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	SetWindowLong(hwnd, GWL_STYLE, style | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION);

	const MARGINS shadow = { 1, 1, 1, 1 };
    //::DwmExtendFrameIntoClientArea(hwnd, &shadow);
}

void FramelessWindowForDialog::setTitleBar(QWidget* titleBar)
{
	this->m_titleBar = titleBar;
	if (!titleBar)
    {
        return;
    }
}

bool FramelessWindowForDialog::nativeEvent(const QByteArray& eventType, void* message, qint64* result)
{
	MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message)
    {
        case WM_NCCALCSIZE :
            {
                *result = 0;
                return true;
            }
        case WM_NCHITTEST :
            {
                long x = GET_X_LPARAM(msg->lParam);
                long y = GET_Y_LPARAM(msg->lParam);
                QPoint mouse_pos(x, y);
                *result = this->adjustResizeWindow(msg->hwnd, mouse_pos);
                if (0 != *result) return true;
                if (!this->m_titleBar) return false;
                // support highdpi
                double dpr = this->devicePixelRatioF();
                QPoint pos = m_titleBar->mapFromGlobal(QPoint(x / dpr, y / dpr));
                if (!this->m_titleBar->rect().contains(pos)) return false;
                QWidget* child = this->m_titleBar->childAt(pos);
                if (!child)
                {
                    *result = HTCAPTION;
                    return true;
                }
                return false;
            }
        // 处理其他消息
        case WM_SHOWWINDOW :
            {
                if (msg->wParam)
                {
                    // 获取窗口句柄
                    auto hwnd = reinterpret_cast<HWND>(this->winId());

                    // 获取屏幕分辨率
                    RECT rect;
                    GetWindowRect(hwnd, &rect);
                    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

                    // 计算窗口位置
                    int windowWidth = rect.right - rect.left;
                    int windowHeight = rect.bottom - rect.top;
                    int posX = (screenWidth - windowWidth) / 2;
                    int posY = (screenHeight - windowHeight) / 2;

                    // 设置窗口位置
                    SetWindowPos(hwnd, HWND_TOP, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                }
                break;
            }
        default :
            break;
    }

    return QDialog::nativeEvent(eventType, message, result);
}

int FramelessWindowForDialog::adjustResizeWindow(HWND hwnd, const QPoint& pos)
{
	int result = 0;

	RECT winrect;
	GetWindowRect(HWND(this->winId()), &winrect);

	int mouse_x = pos.x();
	int mouse_y = pos.y();

	bool resizeWidth = this->minimumWidth() != this->maximumWidth();
	bool resizeHieght = this->minimumHeight() != this->maximumHeight();

    if (resizeWidth)
    {
        if (mouse_x > winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH) result = HTLEFT;
        if (mouse_x < winrect.right && mouse_x >= winrect.right - RESIZE_WINDOW_WIDTH) result = HTRIGHT;
    }

    if (resizeHieght)
    {
        if (mouse_y < winrect.top + RESIZE_WINDOW_WIDTH && mouse_y >= winrect.top) result = HTTOP;

        if (mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH) result = HTBOTTOM;
    }

    if (resizeWidth && resizeHieght)
    {
        // topleft corner
        if (mouse_x >= winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH &&
            mouse_y >= winrect.top && mouse_y < winrect.top + RESIZE_WINDOW_WIDTH)
        {
            result = HTTOPLEFT;
        }

        // topRight corner
        if (mouse_x <= winrect.right && mouse_x > winrect.right - RESIZE_WINDOW_WIDTH &&
            mouse_y >= winrect.top && mouse_y < winrect.top + RESIZE_WINDOW_WIDTH)
            result = HTTOPRIGHT;

        // leftBottom  corner
        if (mouse_x >= winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH &&
            mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOMLEFT;

        // rightbottom  corner
        if (mouse_x <= winrect.right && mouse_x > winrect.right - RESIZE_WINDOW_WIDTH &&
            mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOMRIGHT;
    }
    return result;
}
