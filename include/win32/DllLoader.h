/** @file
 * @brief DLL���I���[�h�T�|�[�g�N���X�̐錾
 *
 * @author ����  �O
 * $Date: 2004/11/20 05:21:49 $
 * $Revision: 1.2 $
 */
#if !defined( DLLLOADER_H_INCLUDE )
#define DLLLOADER_H_INCLUDE

// MFC�g�p���p�ɂ�windows.h�̓C���N���[�h���Ȃ�
#if !defined( __AFXWIN_H__ )
 #include <windows.h>
#endif  // !defined( __AFXWIN_H__ )

#include <memory>

namespace std {
	using namespace std::tr1;
}

#include "win32/SharedType.h"
#include "win32/Win32Exception.h"

/// Win32���b�p�[�N���X�Q
namespace win32
{
	/**
	 *
	 * @brief DLL�̓��I���[�h����
	 * @note
	 *  DllLoader  dll( "DLL��" );\n
	 *  typedef void (*FUNC)();\n
	 *  FUNC func = 0;\n
	 *    .\n
	 *    .\n
	 *    .\n
	 *\n
	 *  // VC++ 6.0�̏ꍇ�̓����o�֐��e���v���[�g�̃e���v���[�g�����ł�\n
	 *  // �������ł��Ȃ��̂Ŗ߂������֐��^�������Ŗ�������B\n
	 *  func = dll.GetProcAddress( "�֐���", func );\n
	 *\n
	 *  // �ꎞ�I�u�W�F�N�g�œn���Ă݂�B\n
	 *  func = dll.GetProcAddress( "�֐���", FUNC() );\n
	 *\n
	 *  // VC++ 7.1(.NET 2003)�̏ꍇ�̓e���v���[�g�����ŉ����ł���̂Ŋ֐��^������\n
	 *  // �w�肵�Ȃ��Ă��悢�B\n
	 *  func = dll.GetProcAddress< FUNC >( "�֐���" );\n
	 */
	class DllLoader
	{
	public:

		// �R���X�g���N�^
		DllLoader();
		DllLoader( const win32::tstring& dllName );

		// �f�X�g���N�^
		~DllLoader();
		
		// DLL�̃I�[�v��
		void Open( const win32::tstring& dllName );

		// DLL�̃N���[�Y
		void Close();

		// DLL�̃I�[�v����Ԃ��擾����
		bool IsOpen() const;

		/**
		 * DLL���̊֐��̃A�h���X���擾
		 *
		 * @param lpProcName �֐���
		 *
		 * @return �֐��A�h���X
		 *
		 * @exception Win32Exception
		 *
		 * @note
		 *  VC++ 6.0�̏ꍇ�����o�֐��e���v���[�g�̓N���X�錾���ɋL�q���Ȃ���
		 * �R���p�C���ł��Ȃ��B
		 */
		template< typename FuncPtr >
		FuncPtr GetProcAddress( const std::string& procName, FuncPtr = 0 )
		{
			FuncPtr func = reinterpret_cast< FuncPtr >( ::GetProcAddress( dll_.get(), procName.c_str() ) );
			if( func == 0 ) {
				Throw_Win32Exception();
			}

			return func;
		}

	private:

		std::shared_ptr< HINSTANCE__ >    dll_;   ///< DLL�n���h��
	};
} // namespace win32

#endif  // !defined( DLLLOADER_H_INCLUDE )
// EOF
