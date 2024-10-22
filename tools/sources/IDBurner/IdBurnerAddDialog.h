#ifndef __IdBurnerAddDialog__
#define __IdBurnerAddDialog__

/**
@file
Subclass of EditDialog, which is generated by wxFormBuilder.
*/

#include "GUIFrame.h"
#include "IdBurnerApp.h"

//// end generated include

/** Implementing EditDialog */
class IdBurnerAddDialog : public EditDialog
{
    private:
        ConfigReader configuration;
        wxTextValidator idValidator;

        std::string &new_name;
	protected:
		// Handlers for EditDialog events.
        void checkCounter( wxCommandEvent& event);
		void onSave( wxCommandEvent& event );
		void onCancel( wxCommandEvent& event );
	public:
		/** Constructor */
		IdBurnerAddDialog( wxWindow* parent , std::string file_path, std::string &name_device);
	//// end generated class members

};

#endif // __IdBurnerAddDialog__
