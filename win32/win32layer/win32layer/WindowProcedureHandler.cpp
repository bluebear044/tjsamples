#include "WindowProcedureHandler.hpp"

#include <map>

using namespace std;

namespace WIN32LAYER {

	static map<HWND, WindowProcedureHandler*> handlers;

	/**
	 * @brief ProcResult
	 */

	ProcResult::ProcResult() : _needDefaultProc(false), resultCode(0) {
	}
	ProcResult::~ProcResult() {
	}

	void ProcResult::setResult(int code) {
		this->resultCode = code;
	}
	void ProcResult::setNeedDefaultProc(bool needDefaultProc) {
		this->_needDefaultProc = needDefaultProc;
	}
	int ProcResult::getResult() {
		return resultCode;
	}
	bool ProcResult::needDefaultProc() {
		return _needDefaultProc;
	}


	ProcResult WindowProcedureHandler::setResult(int result) {
		ProcResult ret;
		ret.setResult(result);
		return ret;
	}
	ProcResult WindowProcedureHandler::needDefaultProc() {
		ProcResult ret;
		ret.setNeedDefaultProc(true);
		return ret;
	}
	ProcResult WindowProcedureHandler::setResultAndNeedDefaultProc(int result) {
		ProcResult ret;
		ret.setResult(result);
		ret.setNeedDefaultProc(true);
		return ret;
	}

	WORD WindowProcedureHandler::getCommand(WPARAM wParam) {
		return LOWORD(wParam);
	}

	/**
	 * @brief WindowProcedureHandler
	 */

	LRESULT CALLBACK WindowProcedureHandler::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		switch (uMsg) {
		case WM_CREATE:
			{
				LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
				WindowProcedureHandler * handler = (WindowProcedureHandler*)cs->lpCreateParams;
				if (handler) {
					handlers[hWnd] = handler;
					ProcResult ret = handler->onProc(hWnd, uMsg, wParam, lParam);
					if (!ret.needDefaultProc()) {
						return ret.getResult();
					}
				}
			}
			break;

		case WM_DESTROY:
			if (handlers.find(hWnd) != handlers.end()) {
					WindowProcedureHandler * handler = handlers[hWnd];
					ProcResult ret = handler->onProc(hWnd, uMsg, wParam, lParam);

					handlers.erase(hWnd);

					if (!ret.needDefaultProc()) {
						return ret.getResult();
					}
				}
			break;

		default:
			{
				if (handlers.find(hWnd) != handlers.end()) {
					WindowProcedureHandler * handler = handlers[hWnd];
					ProcResult ret = handler->onProc(hWnd, uMsg, wParam, lParam);
					if (!ret.needDefaultProc()) {
						return ret.getResult();
					}
				}
			}
			break;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}