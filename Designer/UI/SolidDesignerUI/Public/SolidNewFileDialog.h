#pragma once
#include "SolidDesignerUI.h"
#include "AliceDocumentKind.h"
#include <QDialog>
#include <QString>
#include <QPointer>

class QLineEdit;
class QCheckBox;
class QLabel;
class QWidget;
class QDialogButtonBox;
class QShowEvent;
class QButtonGroup;
class QRadioButton;
namespace sdr
{
    class SOLID_DESIGNER_UI_EXPORT SolidNewFileDialog final : public QDialog
    {
    public:
        enum class TypeId
        {
            Part = 0,
            Assembly = 1,
            Drawing = 2,
            Sketch = 3,
        };

        enum class SubTypeId
        {
            Default = 0,
            Design = 1,
            ECAD = 2,
            Bim = 3,
            Solid = 4,
            Sheetmetal = 5,
            Layout = 6,
        };

        struct NewFileRequest
        {
            TypeId type = TypeId::Part;
            SubTypeId subtype = SubTypeId::Solid;
            alice::DocumentKind fileKind = alice::DocumentKind::Part;
            QString fileName;
            bool useDefaultTemplate = true;
        };

        explicit SolidNewFileDialog(QWidget* parent = nullptr);
        ~SolidNewFileDialog() override;

        /// \brief: Blocking modal helper.
        /// \return true if user clicks OK and the request is valid.
        static bool GetNewFileRequest(QWidget* parent, NewFileRequest& outRequest);

        /// \brief: Current request snapshot (only meaningful after accept()).
        const NewFileRequest& Request() const { return m_request; }

    private:
        void BuildUi_();
        void BuildTypes_();
        void BuildSubTypes_();

        void UpdateSubTypeVisibility_(TypeId type);
        void SyncFromUi_();
        void UpdateOkEnabled_();

        void EnsureSuggestedName_(TypeId type);
        static QString SuggestedName_(TypeId type);
        void FocusFileNameEdit_();

    protected:
        void showEvent(QShowEvent* event) override;

        static alice::DocumentKind MapToDocumentKind_(TypeId type, SubTypeId subtype) noexcept;
        static QString TypeText_(TypeId type);
        static QString SubTypeText_(SubTypeId st);

    private:
        QPointer<QButtonGroup> m_pTypeGroup;
        QPointer<QButtonGroup> m_pSubTypeGroup;

        QPointer<QRadioButton> m_pPartTypeRadioButton;
        QPointer<QRadioButton> m_pAsmTypeRadioButton;
        QPointer<QRadioButton> m_pDrawingTypeRadioButton;
        QPointer<QRadioButton> m_pSketchTypeButton;

        QPointer<QRadioButton> m_pSubDefaultRadioButton;
        QPointer<QRadioButton> m_pSubDesignRadioButton;
        QPointer<QRadioButton> m_pSubECADRadioButton;
        QPointer<QRadioButton> m_pSubBimRadioButton;
        QPointer<QRadioButton> m_pSubSolidRadioButton;
        QPointer<QRadioButton> m_pSubSheetmetalRadioButton;
        QPointer<QRadioButton> m_pSubLayoutRadioButton;

        QPointer<QLineEdit>        m_pFileNameEdit;
        QPointer<QCheckBox>        m_pUseTemplateChkBox;
        QPointer<QLabel>           m_pFileKindLabel;
        QPointer<QDialogButtonBox> m_pButtonBox;

        bool                       m_bUserEditedName = false;
        QString                    m_strLastSuggestedName;

        NewFileRequest             m_request;
    };
}
