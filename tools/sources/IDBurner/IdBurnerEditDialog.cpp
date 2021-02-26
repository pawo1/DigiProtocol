#include "IdBurnerEditDialog.h"

IdBurnerEditDialog::IdBurnerEditDialog( wxWindow* parent , std::string file_path, std::string device_type, std::string &name_device)
:
EditDialog( parent ), configuration( file_path ), idValidator( wxFILTER_ALPHANUMERIC), new_name(name_device)
{
    advanced = false;
    section = device_type;
    old_name = configuration.getRecord(device_type, "name");
   // new_name = name_device;

    this->SetLabel(_("Edit Device Type"));
    ctrlShortCode->Enable(false);
    ctrlShortCode->SetLabel(device_type);
    ctrlDeviceType->SetLabel(old_name);
    ctrlCounterValue->SetLabel(configuration.getRecord(device_type, "counter"));


    ctrlCounterValue->SetValidator(idValidator);
    ctrlShortCode->SetValidator(idValidator);

}

void IdBurnerEditDialog::checkCounter( wxCommandEvent& event ) {
    if(event.IsChecked()) {

        wxMessageDialog dlg(NULL, _("duplicating IDs may result in incorrect operation of devices.\nIt is recommended that you edit this field only to update the record"), _("Warning"), wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxCENTRE);
        dlg.SetOKCancelLabels(_("OK"), _("Cancel"));

        int answer = dlg.ShowModal();
        if(answer == wxID_OK) {
            advanced = true;
            ctrlCounterValue->Enable(true);
        } else
            setCounter->SetValue(false);
   } else {
        advanced = false;
        ctrlCounterValue->Enable(false);
   }
}

void IdBurnerEditDialog::onSave( wxCommandEvent& event )
{
    std::string name = ctrlDeviceType->GetLineText(0).ToStdString();
    std::string counter = ctrlCounterValue->GetLineText(0).ToStdString();

    if(counter.length() < 2) {
        wxMessageBox(_("Counter must be 2 bytes long!"), _(""));
        return;
    }

    if(configuration.existsValue("name", name) && name != old_name) {
        wxMessageBox(_("Device Type name must be unique!"));
    } else {
        configuration.editRecord(section, "name", name);
        new_name = name;
        if(advanced)
            configuration.editRecord(section, "counter", counter);
        EndModal(1);
    }
}

void IdBurnerEditDialog::onCancel( wxCommandEvent& event )
{
    EndModal(0);
}
