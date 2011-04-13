#ifndef DESKTOP_H_INCLUDE
#define DESKTOP_H_INCLUDE

// MFC�g�p���p�ɂ�windows.h�̓C���N���[�h���Ȃ�
#if !defined( __AFXWIN_H__ )
 #include <windows.h>
#endif  // !defined( __AFXWIN_H__ )

#include <memory>

namespace std {
	using namespace std::tr1;
}

namespace win32 {
	class Desktop
	{
	public:

		Desktop();
		~Desktop();

		// �w�肳�ꂽ�X���b�hID�Ɋ֘A�t�����Ă���f�X�N�g�b�v���J��
		void OpenThreadDesktop( DWORD dwThreadId );

		// �f�X�N�g�b�v�����
		void Close();

		// �f�X�N�g�b�v��؂�ւ���
		void Switch();

		// �Ó������m�F����
		bool IsValid() const;

	private:

		// �n���h�������
		static void CloseDesktop( HDESK hDesktop );

		// �n���h�������(GetThreadDesktop�p�ɉ������Ȃ�)
		static void DummyCloseDesktop( HDESK hDesktop );

	private:

		typedef std::shared_ptr<HDESK__> Handle;
		Handle handle_;			//< �f�X�N�g�b�v�n���h��
	};
} // namespace win32

#endif // #ifndef DESKTOP_H_INCLUDE
// EOF
