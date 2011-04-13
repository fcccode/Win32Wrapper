/** @file
 * @brief Win32API��O�N���X�̒�`
 *
 * @author ����  �O
 * $Date: 2004/11/20 05:21:49 $
 * $Revision: 1.3 $
 */
#include "win32/Win32Exception.h"
#include <sstream>

/// Win32���b�p�[�N���X�Q
namespace win32
{
	/**
	 * �R���X�g���N�^
	 *
	 * @param dwResult �G���[�R�[�h
	 */
	Win32Exception::Win32Exception( DWORD errorCode )
		: std::runtime_error( "" )
		, errorCode_( errorCode )
		, errorMessage_( getErrorMessage( errorCode ) )
	{
	}

	Win32Exception::Win32Exception( DWORD errorCode, const std::string& fileName, int lineNo )
		: std::runtime_error( "" )
		, errorCode_( errorCode )
	{
		std::stringstream str;
		str << fileName << "(" << lineNo << "):" << getErrorMessage( errorCode );
		errorMessage_ = str.str();
	}

	/**
	 * �f�X�g���N�^
	 */
	Win32Exception::~Win32Exception()
	{
	}

	/**
	 * �G���[�R�[�h�̎擾
	 *
	 * @return �G���[�R�[�h
	 */
	DWORD Win32Exception::getErrorCode() const
	{
		return errorCode_;
	}

	/**
	 * �G���[���b�Z�[�W�̎擾
	 *
	 * @return �G���[���b�Z�[�W
	 */
	const std::string& Win32Exception::getErrorMessage() const
	{
		return errorMessage_;
	}

	/**
	 * �G���[���b�Z�[�W�̎擾
	 *
	 * @return �G���[���b�Z�[�W
	 */
	const char* Win32Exception::what() const
	{
		return errorMessage_.c_str();
	}

	/**
	 * �G���[�R�[�h����G���[���b�Z�[�W�̎擾(�N���X�֐�)
	 *
	 * @param dwErrCode �G���[�R�[�h
	 *
	 * @return �G���[���b�Z�[�W
	 */
	std::string Win32Exception::getErrorMessage( DWORD errorCode )
	{
		// �G���[���b�Z�[�W�p�N���X
		class ErrorMessage
		{
		public:

			ErrorMessage() : message_(0) {}
			~ErrorMessage(){ if( message_ != 0 ) ::LocalFree( message_ ); }

			char** operator & (){ return &message_; }
			char* get(){ return message_; }

		private:

			char* message_;
		};

		ErrorMessage message; // ���b�Z�[�W�o�b�t�@

		// �G���[���b�Z�[�W�̎擾
		BOOL ret = ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								0, errorCode, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR)&message, 0, 0 );

		return ret ? message.get() : "����`�G���[";
	}
}
// EOF
