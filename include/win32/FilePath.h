/** @file
 * @brief �t�@�C���p�X����N���X�̐錾
 *
 * @author ����  �O
 * $Date: 2004/10/21 11:25:09 $
 * $Revision: 1.1.1.1 $
 */
#if !defined( PATHFILE_H_INCLUDE )
#define PATHFILE_H_INCLUDE

#pragma comment( lib, "shlwapi.lib" )

#include <string>

// MFC�g�p���p�ɂ�windows.h�̓C���N���[�h���Ȃ�
#if !defined( __AFXWIN_H__ )
 #include <windows.h>
#endif  // !defined( __AFXWIN_H__ )

#include <shlwapi.h>

#include "win32/SharedType.h"

/// Win32���b�p�[�N���X�Q
namespace win32
{

	/// �t�@�C���p�X����
	class FilePath
	{
	public:

		// �R���X�g���N�^
		FilePath();
		FilePath( win32::tstring& strPath );
		FilePath( const FilePath& rhs );

		// �f�X�g���N�^
		~FilePath();

		// �p�X��ݒ�
		void SetPath( const win32::tstring& path );
		FilePath& operator = ( const win32::tstring& path );
		FilePath& operator = ( const TCHAR* path );

		// �p�X���擾
		const win32::tstring& GetPath() const;

		//// �p�X�̒ǉ�
		//BOOL AddPath( const win32::tstring& path );

		//// �t�@�C�����̎擾
		//win32::tstring GetFileName() const;

		//// �g���q�̎擾
		//win32::tstring GetExtention() const;
		//// �g���q�̕ύX
		//BOOL RenameExtention( const win32::tstring& strExtention );
		//// �g���q��t��(���Ɋg���q�����Ă��鎞�ɂ͖���)
		//BOOL AddExtention( const win32::tstring& strExtention );
		//// �g���q�̏���
		//void RemoveExtention();

		//// �o�b�N�X���b�V����t��(�p�X�̍Ō�Ƀo�b�N�X���b�V��������ꍇ�͖���)
		//void AddBackslash();
		//// �o�b�N�X���b�V���̍폜
		//void RemoveBackslash();

		//// �u�����N�̏���
		//void RemoveBlanks();

		//// �p�X(�t�@�C����)�����݂��邩�ǂ���
		//BOOL IsExists() const;
		//// �p�X���f�B���N�g�����ǂ���
		//BOOL IsDirectory() const;
		//// �p�X�̃f�B���N�g�����󂩂ǂ���
		//BOOL IsDirectoryEmpty() const;

		//// �p�X�����[�g�p�X���ǂ���
		//BOOL IsRoot() const;
		//// �������[�g�p�X���ǂ���
		//BOOL IsSameRoot( const win32::tstring& strPath ) const;

		//// �J�����g�f�B���N�g���̎擾
		//static win32::tstring GetCurrentDirectory();

		//// �e���|�����p�X�̎擾
		//static win32::tstring GetTempPath();

		// �p�X(�t�@�C����)�����݂��邩�ǂ���
		static bool IsExists( const win32::tstring& path );

		// �t�@�C���̍Ō�̕������폜����
		static win32::tstring RemoveFileSpec( const win32::tstring& path );

	private:

		win32::tstring	path_;
	};

} // namespace win32;

#endif  // !defined( PATHFILE_H_INCLUDE )
// EOF
