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
 * @param lpDllName DLL�t�@�C����
 *
 * @exception Win32Exception
 */
DllLoader::DllLoader( LPCTSTR dllName )
    : dll_()
{
    // DLL���J��
    open( dllName );
}

/**
 * �f�X�g���N�^
 */
DllLoader::~DllLoader()
{
    close();
}

/**
 * DLL�̃I�[�v��
 *
 * @param lpDllName DLL�t�@�C����
 *
 * @exception Win32Exception
 *
 * @pre DLL���쐬
 */
// DLL�̃I�[�v��
void DllLoader::open( LPCTSTR dllName )
{
    dll_ = std::shared_ptr< HINSTANCE__ >( ::LoadLibrary( dllName ), &::FreeLibrary );
    if( dll_.get() == 0 ) {
		throw Win32Exception( ::GetLastError() );
	}
}

/**
 * DLL�̃N���[�Y
 */
void DllLoader::close()
{
    dll_.reset();
}

// DLL�̃I�[�v�����
bool DllLoader::isOpen() const
{
    return dll_.get() != 0;
}

} // namespace win32
// EOF
