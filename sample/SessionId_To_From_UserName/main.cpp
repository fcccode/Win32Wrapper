#include <windows.h>
#include <Lmcons.h>

#include <wtsapi32.h>
#pragma comment( lib, "wtsapi32.lib" )

#include <string>
#include <vector>
#include <iostream>

namespace win32
{
	// WTSFreeMemory�̂��߂̃X�}�|
	template< typename T >
	class AutoWtsPtr {
	public:

		typedef T value_type;
		typedef T* pointer_type;

		AutoWtsPtr() : val_( 0 ) {}
		~AutoWtsPtr() {
			::WTSFreeMemory( val_ );
		}

		pointer_type* operator & () {
			return &val_;
		}

		value_type& operator * () {
			return *val_;
		}

		value_type& operator [] ( size_t index ) {
			return val_[index];
		}

		pointer_type get() {
			return val_;
		}

	private:

		AutoWtsPtr( const AutoWtsPtr& rhs );
		AutoWtsPtr& operator = ( const AutoWtsPtr& rhs );

		pointer_type	val_;
	};

	typedef std::basic_string<TCHAR> tstring;

	win32::tstring GetUserNameFromSessionId( DWORD dwSessionId )
	{
		win32::AutoWtsPtr< TCHAR > pBuffer;
		DWORD BytesReturned = 0;
		BOOL ret =  WTSQuerySessionInformation( WTS_CURRENT_SERVER_HANDLE, dwSessionId, WTSUserName, &pBuffer, &BytesReturned );

		return ret ? win32::tstring( pBuffer.get() ) : win32::tstring();
	}

	DWORD GetSessionIdFromUserName(BSTR bstrUserName)
	{
		// �Z�b�V�����̈ꗗ���擾����
		win32::AutoWtsPtr< WTS_SESSION_INFO > pSessionInfo;
		DWORD count = 0;
		BOOL ret = WTSEnumerateSessions( WTS_CURRENT_SERVER_HANDLE, 0, 1, &pSessionInfo, &count );
		if ( !ret ) {
			return 0;
		}

		// �Z�b�V�����̈ꗗ����A���[�U�[�����擾���A��v�����Z�b�V����ID��Ԃ�
		for ( DWORD i = 0; i < count; ++i ) {
			// ��r�Ώۂ�BSTR�Ȃ̂ŁAWCHAR�ő��肷��
			// �ق����̂̓Z�b�V����ID�Ȃ̂ŁA����ł��悳����
			win32::AutoWtsPtr< WCHAR > pBuffer;
			DWORD BytesReturned = 0;
			ret =  WTSQuerySessionInformationW( WTS_CURRENT_SERVER_HANDLE , pSessionInfo[i].SessionId, WTSUserName, &pBuffer, &BytesReturned );
			if ( !ret ) {
				continue;
			}

			// \\�̈ʒu�܂ł��폜���āA���[�U�[�������o��(ISensLogon�Ή�)
			std::wstring userName( bstrUserName );
			std::wstring::size_type count = userName.rfind( L'\\' );
			if ( count != std::wstring::npos ) {
				userName.erase( userName.begin(), userName.begin() + count + 1 );
			}

			// ���[�U�[������v������A�Z�b�V����ID��Ԃ�
			if ( userName == pBuffer.get() ) {
				return pSessionInfo[i].SessionId;
			}
		}

		return 0;
	}
}

void main()
{
	WCHAR buffer[UNLEN + 1] = { 0 };
	DWORD length = sizeof(buffer) / sizeof(buffer[0]);
	::GetUserNameW( buffer, &length );
	std::wcout << "UserName from ::GetUserName:" << buffer << std::endl;

	DWORD sessionId = win32::GetSessionIdFromUserName( buffer );
	std::wcout << "SessionId:" << sessionId << std::endl;

	win32::tstring userName = win32::GetUserNameFromSessionId( sessionId );
	std::wcout << "UserName from win32::GetUserNameFromSessionId:" << (TCHAR*)&userName[0] << std::endl;
}
