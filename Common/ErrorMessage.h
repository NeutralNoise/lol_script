#ifndef ERROR_MESSAGE_H_INCLUDED
#define ERROR_MESSAGE_H_INCLUDED

#include <string>
#include <vector>
#include <map>

enum ErrorLevel
{
	E_WARNING,
	E_FATAL
};

enum ErrorFrom {
	EF_COMPILER,
	EF_VM,
	EF_UNKNOW
};

enum ErrorString {
	ES_StackOverFlow,
	ES_OutOfMem,
	ES_Unknown
};

struct ErrorMessage {
	int level;
	int from; //!< Was the error from the VM or the compiler.
	std::string msg;

	ErrorMessage() {
		level = ErrorLevel::E_WARNING;
		from = ErrorFrom::EF_UNKNOW;
		msg = "Some error happened.";
	}

	ErrorMessage(const int &level, const int &from, const std::string &msg) {
		this->level = level;
		this->from = from;
		this->msg = msg;
	}


};
//TODO Write defualt OnPrint and OnFatel.
class ErrorHandlerCom
{
public:
	ErrorHandlerCom() {
	
	}

	~ErrorHandlerCom() {

	}

	static void InitErrorHandler() {
		p_instance = new ErrorHandlerCom;
		p_instance->OnPrint = nullptr;
		p_instance->OnFatel = nullptr;
	}

	static void InitErrorHandler(void(*OnPrint)(const ErrorMessage &msg), void(*OnFatel)(const ErrorMessage &msg)) {
		p_instance = new ErrorHandlerCom;
		p_instance->OnPrint = OnPrint;
		p_instance->OnFatel = OnFatel;
	}

	static void Clean() {
		delete p_instance;
	}

	void AddMessage(const ErrorMessage & msg) {
		m_errors.push_back(msg);
		if (msg.level == ErrorLevel::E_FATAL) {
			if (OnPrint != nullptr) {
				PrintErrors();
			}
			if (OnFatel != nullptr) {
				OnFatel(msg);
			}
			else {
				exit(2);
			}
		}
	}

	void AddMessage(const int &level, const std::string &msg) {
		m_errors.push_back(ErrorMessage(level, ErrorFrom::EF_UNKNOW, msg));
		if (level == ErrorLevel::E_FATAL) {
			if (OnPrint != nullptr) {
				PrintErrors();
			}
			if (OnFatel != nullptr) {
				OnFatel(ErrorMessage(level, ErrorFrom::EF_UNKNOW, msg));
			}
			else {
				exit(2);
			}
		}
	}

	void AddMessage(const int &level, const int &from, const int &msg) {
		m_errors.push_back(ErrorMessage(level, ErrorFrom::EF_UNKNOW, ErrorToString(msg)));
		if (level == ErrorLevel::E_FATAL) {
			if (OnPrint != nullptr) {
				PrintErrors();
			}
			if (OnFatel != nullptr) {
				OnFatel(ErrorMessage(level, ErrorFrom::EF_UNKNOW, ErrorToString(msg)));
			}
			else {
				exit(2);
			}
		}
	}

	void AddMessage(const int &level, const int &from, const std::string &msg) {
		m_errors.push_back(ErrorMessage(level, from, msg));
		if (level == ErrorLevel::E_FATAL) {
			if (OnPrint != nullptr) {
				PrintErrors();
			}
			if (OnFatel != nullptr) {
				OnFatel(ErrorMessage(level, from, msg));
			}
			else {
				exit(2);
			}
		}
	}

	void PrintErrors() {
		if (OnPrint != nullptr) {
			for (size_t i = 0; i < m_errors.size(); i++) {
				OnPrint(m_errors[i]);
			}
		}
	}

	void ClearErrors() {
		m_errors.erase(m_errors.begin(), m_errors.end());
	}

	static ErrorHandlerCom * GetInstance() {
		return p_instance;
	}

private:
	std::vector<ErrorMessage> m_errors;
	void (*OnPrint)(const ErrorMessage &msg);
	void(*OnFatel)(const ErrorMessage &msg);
	static ErrorHandlerCom * p_instance;
	std::map<int, std::string> m_MsgStrings;

	std::string ErrorToString(const int &es) {
		switch (es)
		{
		case ErrorString::ES_StackOverFlow:
			return "Stack Overflow";
		case ErrorString::ES_OutOfMem:
			return "Out of Memory";
		default:
			break;
		}
		return "Unknown Error";
	}

};

typedef ErrorHandlerCom EHC;

#endif //ERROR_MESSAGE_H_INCLUDED