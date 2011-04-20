/** @file
 * @brief Win32API��O�N���X�̐錾
 *
 * @author ����  �O
 * $Date: 2004/11/20 05:21:49 $
 * $Revision: 1.3 $
 */
#if !defined( WINEXCEPTION_H_INCLUDE )
#define WINEXCEPTION_H_INCLUDE

// MFC�g�p���p�ɂ�windows.h�̓C���N���[�h���Ȃ�
#if !defined( __AFXWIN_H__ )
 #include <windows.h>
#endif  // !defined( __AFXWIN_H__ )

#include <string>
#include <stdexcept>

/// Win32���b�p�[�N���X�Q
namespace win32
{
#define Throw_Win32Exception() \
	throw win32::Win32Exception( ::GetLastError(), __FILE__, __LINE__ )

    /// Win32��O�N���X
    class Win32Exception : public std::runtime_error
    {
    public:

        // �R���X�g���N�^
        explicit Win32Exception( DWORD errorCode );
		Win32Exception( DWORD errorCode, const std::string& fileName, int lineNo );

        // �f�X�g���N�^
        ~Win32Exception();

        // �G���[�R�[�h�̎擾
        DWORD GetErrorCode() const;
        // �G���[���b�Z�[�W�̎擾
        const std::string& GetErrorMessage() const;

        // �G���[���b�Z�[�W�̎擾
        const char* what() const;

        // �G���[�R�[�h����G���[���b�Z�[�W�̎擾
        static std::string GetErrorMessage( DWORD errorCode );

    private:

        DWORD       errorCode_;     ///< �G���[�R�[�h
        std::string errorMessage_;  ///< �G���[���b�Z�[�W
    };
} // namespace win32

#endif  // !defined( WINEXCEPTION_H_INCLUDE )
// EOF
