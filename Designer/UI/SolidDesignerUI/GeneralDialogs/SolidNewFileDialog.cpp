//Owner: hananiah
#include "SolidNewFileDialog.h"

#include <QAbstractButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QShowEvent>
#include <QTimer>
#include <QVBoxLayout>

#ifdef Q_OS_WIN
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#endif
#include "AliceQxPtrUtils.h"

using namespace sdr;

namespace
{
    static SolidNewFileDialog::TypeId ReadType(const QButtonGroup* pBtnGroup) noexcept
    {
        if (!pBtnGroup)
            return SolidNewFileDialog::TypeId::Part;

        const int id = pBtnGroup->checkedId();
        if (id < 0)
            return SolidNewFileDialog::TypeId::Part;
        return static_cast<SolidNewFileDialog::TypeId>(id);
    }

    static SolidNewFileDialog::SubTypeId ReadSubType(const QButtonGroup* pBtnGroup) noexcept
    {
        if (!pBtnGroup)
            return SolidNewFileDialog::SubTypeId::Default;

        const int id = pBtnGroup->checkedId();
        if (id < 0)
            return SolidNewFileDialog::SubTypeId::Default;
        return static_cast<SolidNewFileDialog::SubTypeId>(id);
    }

    static void EnsureCheckedVisible(QButtonGroup& oGroup)
    {
        if (auto* pCheckedBtn = oGroup.checkedButton())
        {
            if (pCheckedBtn->isVisible() && pCheckedBtn->isEnabled())
                return;
        }

        // Pick the first visible+enabled button.
        for (auto* pButton : oGroup.buttons())
        {
            if (pButton && pButton->isVisible() && pButton->isEnabled())
            {
                pButton->setChecked(true);
                return;
            }
        }
    }
}

SolidNewFileDialog::SolidNewFileDialog(QWidget* parent)
    : QDialog(parent)
{
    setObjectName("SolidNewFileDialog");
    setWindowTitle(tr("New"));
    setModal(true);
    setMinimumSize(520, 360);

    // Windows UX: remove the '?' context-help button and avoid showing an app icon.
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    setAttribute(Qt::WA_NativeWindow, true);

    BuildUi_();
    BuildTypes_();
    BuildSubTypes_();

    // Default selections
    if (m_pPartTypeRadioButton)
        m_pPartTypeRadioButton->setChecked(true);
    UpdateSubTypeVisibility_(TypeId::Part);
    EnsureSuggestedName_(TypeId::Part);
    if (m_pUseTemplateChkBox)
        m_pUseTemplateChkBox->setChecked(true);

    // Wire events (no per-dialog stylesheet; follow ThemeSupport global palette/qss)
    auto onTypeChanged = [this](TypeId type, bool checked) {
        if (!checked)
            return;
        UpdateSubTypeVisibility_(type);
        EnsureSuggestedName_(type);
        SyncFromUi_();
        UpdateOkEnabled_();
        FocusFileNameEdit_();
    };

    if (m_pPartTypeRadioButton)     
        QObject::connect(m_pPartTypeRadioButton,     &QRadioButton::toggled, this, [=](bool c) { onTypeChanged(TypeId::Part, c); });
    if (m_pAsmTypeRadioButton) 
        QObject::connect(m_pAsmTypeRadioButton, &QRadioButton::toggled, this, [=](bool c) { onTypeChanged(TypeId::Assembly, c); });
    if (m_pDrawingTypeRadioButton)  
        QObject::connect(m_pDrawingTypeRadioButton,  &QRadioButton::toggled, this, [=](bool c) { onTypeChanged(TypeId::Drawing, c); });
    if (m_pSketchTypeButton)  
        QObject::connect(m_pSketchTypeButton,   &QRadioButton::toggled, this, [=](bool c) { onTypeChanged(TypeId::Sketch, c); });

    auto onSubTypeChanged = [this](bool checked) {
        if (!checked)
            return;
        SyncFromUi_();
        UpdateOkEnabled_();
        FocusFileNameEdit_();
    };
    if (m_pSubDefaultRadioButton)   
        QObject::connect(m_pSubDefaultRadioButton,    &QRadioButton::toggled, this, onSubTypeChanged);
    if (m_pSubDesignRadioButton)
        QObject::connect(m_pSubDesignRadioButton, &QRadioButton::toggled, this, onSubTypeChanged);
    if (m_pSubBimRadioButton)
        QObject::connect(m_pSubBimRadioButton, &QRadioButton::toggled, this, onSubTypeChanged);
    if (m_pSubSolidRadioButton)     
        QObject::connect(m_pSubSolidRadioButton,      &QRadioButton::toggled, this, onSubTypeChanged);
    if (m_pSubSheetmetalRadioButton) 
        QObject::connect(m_pSubSheetmetalRadioButton, &QRadioButton::toggled, this, onSubTypeChanged);
    if (m_pSubLayoutRadioButton)     
        QObject::connect(m_pSubLayoutRadioButton,     &QRadioButton::toggled, this, onSubTypeChanged);

    if (m_pFileNameEdit)
    {
        QObject::connect(m_pFileNameEdit, &QLineEdit::textChanged, this, [this](const QString&) {
            SyncFromUi_();
            UpdateOkEnabled_();
        });

        QObject::connect(m_pFileNameEdit, &QLineEdit::textEdited, this, [this](const QString&) {
            m_bUserEditedName = true;
        });
    }

    if (m_pUseTemplateChkBox)
    {
        QObject::connect(m_pUseTemplateChkBox, &QCheckBox::toggled, this, [this](bool) {
            SyncFromUi_();
            UpdateOkEnabled_();
        });
    }

    SyncFromUi_();
    UpdateOkEnabled_();

    // Ensure the line edit has focus when the dialog becomes visible.
    QTimer::singleShot(0, this, [this]() {
        FocusFileNameEdit_();
    });
}

SolidNewFileDialog::~SolidNewFileDialog() = default;

bool SolidNewFileDialog::GetNewFileRequest(QWidget* parent, NewFileRequest& outRequest)
{
    SolidNewFileDialog dlg(parent);
    if (dlg.exec() != QDialog::Accepted)
        return false;

    outRequest = dlg.Request();
    return !outRequest.fileName.trimmed().isEmpty();
}

void SolidNewFileDialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    FocusFileNameEdit_();
}

void SolidNewFileDialog::FocusFileNameEdit_()
{
    if (!m_pFileNameEdit)
        return;

    m_pFileNameEdit->setFocus(Qt::TabFocusReason);
    if (!m_pFileNameEdit->text().isEmpty())
        m_pFileNameEdit->selectAll();
}

QString SolidNewFileDialog::SuggestedName_(TypeId type)
{
    switch (type)
    {
    case TypeId::Part:
        return QStringLiteral("Part1");
    case TypeId::Assembly:
        return QStringLiteral("Assembly1");
    case TypeId::Drawing:
        return QStringLiteral("Drawing1");
    case TypeId::Sketch:
        return QStringLiteral("Sketch1");
    default:
        return QStringLiteral("Part1");
    }
}

void SolidNewFileDialog::EnsureSuggestedName_(TypeId type)
{
    if (!m_pFileNameEdit)
        return;

    const QString cur = m_pFileNameEdit->text().trimmed();
    const QString next = SuggestedName_(type);

    // Only override the edit when user didn't type anything meaningful.
    const bool canOverride = (!m_bUserEditedName) || cur.isEmpty() || (!m_strLastSuggestedName.isEmpty() && cur == m_strLastSuggestedName);
    if (!canOverride)
        return;

    m_strLastSuggestedName = next;
    m_bUserEditedName = false; // still in auto mode

    m_pFileNameEdit->setText(next);
    m_pFileNameEdit->setCursorPosition(0);
    m_pFileNameEdit->selectAll();
}

void SolidNewFileDialog::BuildUi_()
{
    auto* pRootLayout = QX_NEW_QOBJECT(QVBoxLayout, this);
    DIAG_RETURN_VOID_IF_FALSE(pRootLayout, "pRootLayout is null", "hananiah", "2025.12.25");
    pRootLayout->setContentsMargins(12, 12, 12, 12);
    pRootLayout->setSpacing(10);

    // Top row: Type / Sub-type
    auto* pTopRowLayout = QX_NEW_QOBJECT(QHBoxLayout);
    DIAG_RETURN_VOID_IF_FALSE(pTopRowLayout, "pTopRowLayout is null", "hananiah", "2025.12.25");
    pTopRowLayout->setSpacing(12);
    pRootLayout->addLayout(pTopRowLayout, 1);

    auto* pTypeGroupBox = QX_NEW_QWIDGET(QGroupBox, tr("Type"), this);
    DIAG_RETURN_VOID_IF_FALSE(pTypeGroupBox, "pTypeGroupBox is null", "hananiah", "2025.12.25");
    auto* pSubTypeGroupBox = QX_NEW_QWIDGET(QGroupBox, tr("Sub-type"), this);
    DIAG_RETURN_VOID_IF_FALSE(pSubTypeGroupBox, "pSubTypeGroupBox is null", "hananiah", "2025.12.25");
    pTopRowLayout->addWidget(pTypeGroupBox, 1);
    pTopRowLayout->addWidget(pSubTypeGroupBox, 1);

    auto* pTypeVLayout = QX_NEW_QOBJECT(QVBoxLayout, pTypeGroupBox);
    DIAG_RETURN_VOID_IF_FALSE(pTypeVLayout, "pTypeVLayout is null", "hananiah", "2025.12.25");
    pTypeVLayout->setContentsMargins(12, 16, 12, 12);
    pTypeVLayout->setSpacing(6);

    auto* pSubTypeVLayout = QX_NEW_QOBJECT(QVBoxLayout, pSubTypeGroupBox);
    DIAG_RETURN_VOID_IF_FALSE(pSubTypeVLayout, "pSubTypeVLayout is null", "hananiah", "2025.12.25");
    pSubTypeVLayout->setContentsMargins(12, 16, 12, 12);
    pSubTypeVLayout->setSpacing(6);

    // Create button groups
    m_pTypeGroup = QX_NEW_QOBJECT(QButtonGroup, this);
    DIAG_RETURN_VOID_IF_FALSE(m_pTypeGroup, "m_pTypeGroup is null", "hananiah", "2025.12.25");
    m_pSubTypeGroup = QX_NEW_QOBJECT(QButtonGroup, this);
    DIAG_RETURN_VOID_IF_FALSE(m_pSubTypeGroup, "m_pSubTypeGroup is null", "hananiah", "2025.12.25");
    m_pTypeGroup->setExclusive(true);
    m_pSubTypeGroup->setExclusive(true);

    // Type radios
    m_pPartTypeRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Part"), pTypeGroupBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pPartTypeRadioButton, "m_pPartTypeRadioButton is null", "hananiah", "2025.12.25");
    m_pAsmTypeRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Assembly"), pTypeGroupBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pAsmTypeRadioButton, "m_pAsmTypeRadioButton is null", "hananiah", "2025.12.25");
    m_pDrawingTypeRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Drawing"), pTypeGroupBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pDrawingTypeRadioButton, "m_pDrawingTypeRadioButton is null", "hananiah", "2025.12.25");
    m_pSketchTypeButton = QX_NEW_QWIDGET(QRadioButton, tr("Sketch"), pTypeGroupBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pSketchTypeButton, "m_pSketchTypeButton is null", "hananiah", "2025.12.25");

    pTypeVLayout->addWidget(m_pPartTypeRadioButton);
    pTypeVLayout->addWidget(m_pAsmTypeRadioButton);
    pTypeVLayout->addWidget(m_pDrawingTypeRadioButton);
    pTypeVLayout->addWidget(m_pSketchTypeButton);
    pTypeVLayout->addStretch(1);

    m_pTypeGroup->addButton(m_pPartTypeRadioButton, static_cast<int>(TypeId::Part));
    m_pTypeGroup->addButton(m_pAsmTypeRadioButton, static_cast<int>(TypeId::Assembly));
    m_pTypeGroup->addButton(m_pDrawingTypeRadioButton, static_cast<int>(TypeId::Drawing));
    m_pTypeGroup->addButton(m_pSketchTypeButton, static_cast<int>(TypeId::Sketch));

    // Sub-type radios (all created once; visibility controlled by type)
    m_pSubDefaultRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Default"), pSubTypeGroupBox);
    m_pSubDesignRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Design"), pSubTypeGroupBox);
    m_pSubECADRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("ECAD"), pSubTypeGroupBox);
    m_pSubBimRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("BIM"), pSubTypeGroupBox);
    m_pSubSolidRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Solid"), pSubTypeGroupBox);
    m_pSubSheetmetalRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Sheetmetal"), pSubTypeGroupBox);
    m_pSubLayoutRadioButton = QX_NEW_QWIDGET(QRadioButton, tr("Layout"), pSubTypeGroupBox);

    pSubTypeVLayout->addWidget(m_pSubDefaultRadioButton);
    pSubTypeVLayout->addWidget(m_pSubDesignRadioButton);
    pSubTypeVLayout->addWidget(m_pSubECADRadioButton);
    pSubTypeVLayout->addWidget(m_pSubBimRadioButton);
    pSubTypeVLayout->addWidget(m_pSubSolidRadioButton);
    pSubTypeVLayout->addWidget(m_pSubSheetmetalRadioButton);
    pSubTypeVLayout->addWidget(m_pSubLayoutRadioButton);
    pSubTypeVLayout->addStretch(1);

    m_pSubTypeGroup->addButton(m_pSubDefaultRadioButton, static_cast<int>(SubTypeId::Default));
    m_pSubTypeGroup->addButton(m_pSubDesignRadioButton, static_cast<int>(SubTypeId::Design));
    m_pSubTypeGroup->addButton(m_pSubECADRadioButton, static_cast<int>(SubTypeId::ECAD));
    m_pSubTypeGroup->addButton(m_pSubBimRadioButton, static_cast<int>(SubTypeId::Bim));
    m_pSubTypeGroup->addButton(m_pSubSolidRadioButton, static_cast<int>(SubTypeId::Solid));
    m_pSubTypeGroup->addButton(m_pSubSheetmetalRadioButton, static_cast<int>(SubTypeId::Sheetmetal));
    m_pSubTypeGroup->addButton(m_pSubLayoutRadioButton, static_cast<int>(SubTypeId::Layout));

    // Bottom: Settings
    auto* pSettingsGrpBox = QX_NEW_QWIDGET(QGroupBox, tr("Settings"), this);
    DIAG_RETURN_VOID_IF_FALSE(pSettingsGrpBox, "pSettingsGrpBox is null", "hananiah", "2025.12.25");
    pRootLayout->addWidget(pSettingsGrpBox);
    auto* pFormLayout = QX_NEW_QOBJECT(QFormLayout, pSettingsGrpBox);
    DIAG_RETURN_VOID_IF_FALSE(pFormLayout, "pFormLayout is null", "hananiah", "2025.12.25");
    pFormLayout->setContentsMargins(12, 16, 12, 12);
    pFormLayout->setHorizontalSpacing(12);
    pFormLayout->setVerticalSpacing(8);

    m_pFileNameEdit = QX_NEW_QWIDGET(QLineEdit, pSettingsGrpBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pFileNameEdit, "m_pFileNameEdit is null", "hananiah", "2025.12.25");
    m_pFileNameEdit->setPlaceholderText(tr("Name (e.g. Part1)"));
    pFormLayout->addRow(tr("File name"), m_pFileNameEdit);

    m_pUseTemplateChkBox = QX_NEW_QWIDGET(QCheckBox, tr("Use default template"), pSettingsGrpBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pUseTemplateChkBox, "m_pUseTemplateChkBox is null", "hananiah", "2025.12.25");
    pFormLayout->addRow(QString(), m_pUseTemplateChkBox);

    m_pFileKindLabel = QX_NEW_QWIDGET(QLabel, pSettingsGrpBox);
    DIAG_RETURN_VOID_IF_FALSE(m_pFileKindLabel, "m_pFileKindLabel is null", "hananiah", "2025.12.25");
    m_pFileKindLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    pFormLayout->addRow(tr("DocumentKind"), m_pFileKindLabel);

    // Buttons
    m_pButtonBox = QX_NEW_QWIDGET(QDialogButtonBox, QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    DIAG_RETURN_VOID_IF_FALSE(m_pButtonBox, "m_pButtonBox is null", "hananiah", "2025.12.25");
    pRootLayout->addWidget(m_pButtonBox);
    QObject::connect(m_pButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(m_pButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    if (QPushButton* pOkBtn = qobject_cast<QPushButton*>(m_pButtonBox->button(QDialogButtonBox::Ok)))
        pOkBtn->setDefault(true);
}

void SolidNewFileDialog::BuildTypes_()
{
    // Types are built once in BuildUi_. This function exists to keep API stable and explicit.
}

void SolidNewFileDialog::BuildSubTypes_()
{
    // Sub-types are built once in BuildUi_. This function exists to keep API stable and explicit.
}

void SolidNewFileDialog::UpdateSubTypeVisibility_(TypeId type)
{
    auto vis = [](QRadioButton* pRadioButton, bool bValue) {
        if (!pRadioButton)
            return;
        pRadioButton->setVisible(bValue);
        pRadioButton->setEnabled(bValue);
    };

    // Reset all.
    vis(m_pSubDefaultRadioButton, false);
    vis(m_pSubDesignRadioButton, false);
    vis(m_pSubECADRadioButton, false);
    vis(m_pSubBimRadioButton, false);
    vis(m_pSubSolidRadioButton, false);
    vis(m_pSubSheetmetalRadioButton, false);
    vis(m_pSubLayoutRadioButton, false);

    switch (type)
    {
    case TypeId::Part:
        vis(m_pSubSolidRadioButton, true);
        vis(m_pSubSheetmetalRadioButton, true);
        break;
    case TypeId::Drawing:
        vis(m_pSubDefaultRadioButton, true);
        vis(m_pSubLayoutRadioButton, true);
        break;
    case TypeId::Assembly:
        vis(m_pSubDesignRadioButton, true);
        vis(m_pSubBimRadioButton, true);
        break;
    case TypeId::Sketch:
    default:
        vis(m_pSubDefaultRadioButton, true);
        break;
    }

    if (m_pSubTypeGroup)
        EnsureCheckedVisible(*m_pSubTypeGroup);
}

void SolidNewFileDialog::SyncFromUi_()
{
    const TypeId type = ReadType(m_pTypeGroup);
    const SubTypeId sub = ReadSubType(m_pSubTypeGroup);

    m_request.type = type;
    m_request.subtype = sub;
    m_request.fileKind = MapToDocumentKind_(type, sub);
    m_request.fileName = m_pFileNameEdit ? m_pFileNameEdit->text().trimmed() : QString();
    m_request.useDefaultTemplate = m_pUseTemplateChkBox ? m_pUseTemplateChkBox->isChecked() : true;

    QString kindText;
    switch (m_request.fileKind)
    {
    case alice::DocumentKind::Part:
        kindText = tr("Part");
        break;
    case alice::DocumentKind::Assembly:
        kindText = tr("Assembly");
        break;
    case alice::DocumentKind::Drawing:
        kindText = tr("Drawing");
        break;
    case alice::DocumentKind::Sketch:
        kindText = tr("Sketch");
        break;
    default:
        kindText = tr("Unknown");
        break;
    }

    if (m_pFileKindLabel)
        m_pFileKindLabel->setText(kindText);
}

void SolidNewFileDialog::UpdateOkEnabled_()
{
    if (!m_pButtonBox || !m_pFileNameEdit)
        return;

    const bool ok = !m_pFileNameEdit->text().trimmed().isEmpty();
    if (QAbstractButton* pBtn = m_pButtonBox->button(QDialogButtonBox::Ok))
        pBtn->setEnabled(ok);
}

alice::DocumentKind SolidNewFileDialog::MapToDocumentKind_(TypeId type, SubTypeId /*subtype*/) noexcept
{
    // conventional mapping in Alice:
    // - Part/Solid/Sheetmetal -> DocumentKind::Part
    // - Assembly -> DocumentKind::Assembly
    // - Drawing/Layout -> DocumentKind::Drawing
    // - Sketch -> DocumentKind::Sketch
    switch (type)
    {
    case TypeId::Part: 
        return alice::DocumentKind::Part;
    case TypeId::Assembly: 
        return alice::DocumentKind::Assembly;
    case TypeId::Drawing: 
        return alice::DocumentKind::Drawing;
    case TypeId::Sketch: 
        return alice::DocumentKind::Sketch;
    default: 
        return alice::DocumentKind::Part;
    }
}

QString SolidNewFileDialog::TypeText_(TypeId type)
{
    switch (type)
    {
    case TypeId::Part: 
        return tr("Part");
    case TypeId::Assembly:
        return tr("Assembly");
    case TypeId::Drawing: 
        return tr("Drawing");
    case TypeId::Sketch:
        return tr("Sketch");
    default:
        return tr("Part");
    }
}

QString SolidNewFileDialog::SubTypeText_(SubTypeId st)
{
    switch (st)
    {
    case SubTypeId::Default:
        return tr("Default");
    case SubTypeId::Solid: 
        return tr("Solid");
    case SubTypeId::Sheetmetal:
        return tr("Sheetmetal");
    case SubTypeId::Layout: 
        return tr("Layout");
    default: 
        return tr("Default");
    }
}
