#include "IdBurnerAboutDialog.h"

IdBurnerAboutDialog::IdBurnerAboutDialog( wxWindow* parent )
:
AboutDialog( parent )
{

}

void IdBurnerAboutDialog::OnClick( wxCommandEvent& event )
{
    EndModal(0);
}
