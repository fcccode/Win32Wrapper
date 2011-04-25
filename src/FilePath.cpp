/** @file
 * @brief �t�@�C���p�X����N���X�̒�`
 *
 * @author ����  �O
 * $Date: 2004/10/21 11:25:09 $
 * $Revision: 1.1.1.1 $
 */
#include <vector>

#include "win32/FilePath.h"
#include "win32/Win32Exception.h"

namespace win32 {
	// �R���X�g���N�^
	FilePath::FilePath()
	{
	}

	// �R���X�g���N�^
	FilePath::FilePath( win32::tstring& strPath )
	{
		SetPath( strPath );
	}

	// �R���X�g���N�^
	FilePath::FilePath( const FilePath& rhs )
	{
		SetPath( rhs.path_ );
	}

	// �f�X�g���N�^
	FilePath::~FilePath()
	{
	}

	// �p�X��ݒ�
	void FilePath::SetPath( const win32::tstring& path )
	{
		path_ = path;
	}

	FilePath& FilePath::operator = ( const win32::tstring& path )
	{
		SetPath( path );
		return *this;
	}

	FilePath& FilePath::operator = ( const TCHAR* path )
	{
		SetPath( path );
		return *this;
	}


	// �p�X���擾
	const win32::tstring& FilePath::GetPath() const
	{
		return path_;
	}

	//// �p�X�̒ǉ�
	//BOOL FilePath::AddPath( const win32::tstring& path )
	//{
	//	return ::PathAppend( path_, strPath );
	//}

	//// �t�@�C�����̎擾
	//win32::tstring FilePath::GetFileName() const
	//{
	//	return win32::tstring( ::PathFindFileName( path_.c_str() ) );
	//}

	//// �g���q�̎擾
	//win32::tstring FilePath::GetExtention() const
	//{
	//	return win32::tstring( ::PathFindExtension( path_.c_str() ) );
	//}

	//// �g���q�̕ύX
	//BOOL FilePath::RenameExtention( const win32::tstring& strExtention )
	//{
	//	return( ::PathRenameExtension( path_, strExtention ) );
	//}

	//// �g���q��t��(���Ɋg���q�����Ă��鎞�ɂ͖���)
	//BOOL FilePath::AddExtention( const win32::tstring& strExtention )
	//{
	//	return( ::PathAddExtension( path_, strExtention ) );
	//}

	//// �g���q�̏���
	//void FilePath::RemoveExtention()
	//{
	//	::PathRemoveExtension( path_ );
	//}

	//// �o�b�N�X���b�V����t��(�p�X�̍Ō�Ƀo�b�N�X���b�V��������ꍇ�͖���)
	//void FilePath::AddBackslash()
	//{
	//	::PathAddBackslash( path_ );
	//}

	//// �o�b�N�X���b�V���̍폜
	//void FilePath::RemoveBackslash()
	//{
	//	::PathRemoveBackslash( path_ );
	//}

	//// �u�����N�̏���
	//void FilePath::RemoveBlanks()
	//{
	//	::PathRemoveBlanks( path_ );
	//}

	//// �p�X(�t�@�C����)�����݂��邩�ǂ���
	//BOOL FilePath::IsExists() const
	//{
	//	return( ::PathFileExists( path_ ) );
	//}

	// �p�X(�t�@�C����)�����݂��邩�ǂ���
	/*static*/ bool FilePath::IsExists( const win32::tstring& path )
	{
		return ::PathFileExists( path.c_str() );
	}

	//// �p�X���f�B���N�g�����ǂ���
	//BOOL FilePath::IsDirectory() const
	//{
	//	return( ::PathIsDirectory( path_ ) );
	//}

	//// �p�X�̃f�B���N�g�����󂩂ǂ���
	//BOOL FilePath::IsDirectoryEmpty() const
	//{
	//// SDK���A�b�v�f�[�g���Ȃ��Ǝg���Ȃ�?
	////    return( ::PathIsDirectoryEmpty( path_ ) );
	//	return( FALSE );
	//}

	//// �p�X�����[�g�p�X���ǂ���
	//BOOL FilePath::IsRoot() const
	//{
	//	return( ::PathIsRoot( path_ ) );
	//}

	//// �������[�g�p�X���ǂ���
	//BOOL FilePath::IsSameRoot( const win32::tstring& strPath ) const
	//{
	//	return( ::PathIsSameRoot( path_, strPath ) );
	//}

	//// �J�����g�f�B���N�g���̎擾
	///*static*/ win32::tstring FilePath::GetCurrentDirectory()
	//{
	//	TCHAR	path[MAX_PATH] = { 0 };
	//	DWORD ret = ::GetCurrentDirectory( sizeof(path), path );
	//	if ( ret == 0 ) { 
	//		Throw_Win32Exception();
	//	}

	//	return std::string( path );
	//}

	//// �e���|�����p�X�̎擾
	///*static*/ win32::tstring FilePath::GetTempPath()
	//{
	//	TCHAR	tempPath[MAX_PATH];
	//	DWORD ret = ::GetTempPath( sizeof(tempPath), tempPath );
	//	if ( ret == 0 ) { 
	//		Throw_Win32Exception();
	//	}

	//	return win32::tstring( tempPath );
	//}

	// �t�@�C���̍Ō�̕������폜����
	/*static*/ win32::tstring FilePath::RemoveFileSpec( const win32::tstring& path )
	{
		std::vector< win32::tstring::value_type > str( path.begin(), path.end() );
		BOOL ret = ::PathRemoveFileSpec( &str[0] );
		if ( !ret ) {
			Throw_Win32Exception();
		}

		return win32::tstring( &str[0] );
	}
}
// EOF
