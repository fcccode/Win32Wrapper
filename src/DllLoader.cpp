/** @file
 * @brief DLL���I���[�h�T�|�[�g�N���X�̒�`
 *
 * @author ����  �O
 * $Date: 2004/11/20 05:21:49 $
 * $Revision: 1.2 $
 */
#include "win32/DllLoader.h"
#include "win32/Win32Exception.h"

/// Win32���b�p�[�N���X�Q
namespace win32
{

/**
 *�R���X�g���N�^
 */
DllLoader::DllLoader()
    : dll_()
{
}

/**
 * �R���X�g���N�^
 *
 * @param dllName DLL�t�@�C����
 */
DllLoader::DllLoader( const win32::tstring& dllName )
    : dll_()
{
    // DLL���J��
    Open( dllName );
}

/**
 * �f�X�g���N�^
 */
DllLoader::~DllLoader()
{
    Close();
}

/**
 * DLL�̃I�[�v��
 *
 * @param dllName DLL�t�@�C����
 */
// DLL�̃I�[�v��
void DllLoader::Open( const win32::tstring& dllName )
{
	dll_ = std::shared_ptr< HINSTANCE__ >( ::LoadLibrary( dllName.c_str() ), &::FreeLibrary );
    if( dll_.get() == 0 ) {
		Throw_Win32Exception();
	}
}

/// DLL�̃N���[�Y
void DllLoader::Close()
{
    dll_.reset();
}

/// DLL�̃I�[�v�����
bool DllLoader::IsOpen() const
{
    return dll_.get() != 0;
}

} // namespace win32
// EOF
