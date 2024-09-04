/****************************************************************************
** $Id:  qt/qstyle.h   3.0.5   edited May 7 22:37 $
**
** Definition of QStyle class
**
** Created : 980616
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of the kernel module of the Qt GUI Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid Qt Enterprise Edition or Qt Professional Edition
** licenses may use this file in accordance with the Qt Commercial License
** Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/
#ifndef QSTYLE_H
#define QSTYLE_H

#ifndef QT_H
#include "qobject.h"
#endif // QT_H


#ifndef QT_NO_STYLE

class QPopupMenu;
class QStylePrivate;
class QMenuItem;
class QTab;
class QListViewItem;

class QStyleOption {
public:
    enum StyleOptionDefault { Default };

    QStyleOption(StyleOptionDefault=Default) : def(TRUE) {}

    // Note: we don't use default arguments since that is unnecessary
    // initialization.
    QStyleOption(int in1, int in2) :
	def(FALSE), i1(in1), i2(in2) {}
    QStyleOption(int in1, int in2, int in3, int in4) :
	def(FALSE), i1(in1), i2(in2), i3(in3), i4(in4) {}
    QStyleOption(QMenuItem* m) : def(FALSE), mi(m) {}
    QStyleOption(QMenuItem* m, int in1) : def(FALSE), mi(m), i1(in1) {}
    QStyleOption(QMenuItem* m, int in1, int in2) : def(FALSE), mi(m), i1(in1), i2(in2) {}
    QStyleOption(const QColor& c) : def(FALSE), cl(&c) {}
    QStyleOption(QTab* t) : def(FALSE), tb(t) {}
    QStyleOption(QListViewItem* i) : def(FALSE), li(i) {}
    QStyleOption(Qt::ArrowType a) : def(FALSE), i1((int)a) {}

    bool isDefault() const { return def; }

    int lineWidth() const { return i1; }
    int midLineWidth() const { return i2; }
    int frameShape() const { return i3; }
    int frameShadow() const { return i4; }

    QMenuItem* menuItem() const { return mi; }
    int maxIconWidth() const { return i1; }
    int tabWidth() const { return i2; }

    const QColor& color() const { return *cl; }

    QTab* tab() const { return tb; }

    QListViewItem* listViewItem() const { return li; }

    Qt::ArrowType arrowType() const { return (Qt::ArrowType)i1; }

private:
    // NOTE: none of these components have constructors.
    bool def;
    bool b1,b2,b3; // reserved
    QMenuItem* mi;
    QTab* tb;
    QListViewItem* li;
    const QColor* cl;
    int i1, i2, i3, i4;
    int i5, i6; // reserved
    void *p1, *p2, *p3, *p4, *p5; // reserved
    // (padded to 64 bytes on some architectures)
};

class QStyleHintReturn; // not defined yet

class Q_EXPORT QStyle: public QObject
{
    Q_OBJECT

public:
    QStyle();
    virtual ~QStyle();

    // New QStyle API - most of these should probably be pure virtual

    virtual void polish( QWidget * );
    virtual void unPolish( QWidget * );

    virtual void polish( QApplication * );
    virtual void unPolish( QApplication * );

    virtual void polish( QPalette & );

    virtual void polishPopupMenu( QPopupMenu* ) = 0;

    virtual QRect itemRect( QPainter *p, const QRect &r,
			    int flags, bool enabled,
			    const QPixmap *pixmap,
			    const QString &text, int len = -1 ) const;

    virtual void drawItem( QPainter *p, const QRect &r,
			   int flags, const QColorGroup &g, bool enabled,
			   const QPixmap *pixmap, const QString &text,
			   int len = -1, const QColor *penColor = 0 ) const;


    enum PrimitiveElement {
	PE_ButtonCommand,
	PE_ButtonDefault,
	PE_ButtonBevel,
	PE_ButtonTool,
	PE_ButtonDropDown,

	PE_FocusRect,

	PE_ArrowUp,
	PE_ArrowDown,
	PE_ArrowRight,
	PE_ArrowLeft,

	PE_SpinWidgetUp,
	PE_SpinWidgetDown,
	PE_SpinWidgetPlus,
	PE_SpinWidgetMinus,

	PE_Indicator,
	PE_IndicatorMask,
	PE_ExclusiveIndicator,
	PE_ExclusiveIndicatorMask,

	PE_DockWindowHandle,
	PE_DockWindowSeparator,
	PE_DockWindowResizeHandle,

	PE_Splitter,

	PE_Panel,
	PE_PanelPopup,
	PE_PanelMenuBar,
	PE_PanelDockWindow,

	PE_TabBarBase,

	PE_HeaderSection,
	PE_HeaderArrow,
	PE_StatusBarSection,

	PE_GroupBoxFrame,

	PE_Separator,

	PE_SizeGrip,

	PE_CheckMark,

	PE_ScrollBarAddLine,
	PE_ScrollBarSubLine,
	PE_ScrollBarAddPage,
	PE_ScrollBarSubPage,
	PE_ScrollBarSlider,
	PE_ScrollBarFirst,
	PE_ScrollBarLast,

	PE_ProgressBarChunk,

	PE_PanelLineEdit,
	PE_PanelTabWidget,

	PE_WindowFrame,

	// do not add any values below/greater this
	PE_CustomBase =			0xf000000
    };

    enum StyleFlags {
	Style_Default = 		0x00000000,
	Style_Enabled = 		0x00000001,
	Style_Raised =			0x00000002,
	Style_Sunken =	 		0x00000004,
	Style_Off =			0x00000008,
	Style_NoChange =		0x00000010,
	Style_On =			0x00000020,
	Style_Down =			0x00000040,
	Style_Horizontal =		0x00000080,
	Style_HasFocus =		0x00000100,
	Style_Top =			0x00000200,
	Style_Bottom =			0x00000400,
	Style_FocusAtBorder =		0x00000800,
	Style_AutoRaise =		0x00001000,
	Style_MouseOver =		0x00002000,
	Style_Up =			0x00004000,
	Style_Selected =	 	0x00008000,
	Style_Active =			0x00010000,
	Style_ButtonDefault =		0x00020000
    };
    typedef uint SFlags;

    virtual void drawPrimitive( PrimitiveElement pe,
				QPainter *p,
				const QRect &r,
				const QColorGroup &cg,
				SFlags flags = Style_Default,
				const QStyleOption& = QStyleOption::Default ) const = 0;


    enum ControlElement {
	CE_PushButton,
	CE_PushButtonLabel,

	CE_CheckBox,
	CE_CheckBoxLabel,

	CE_RadioButton,
	CE_RadioButtonLabel,

	CE_TabBarTab,
	CE_TabBarLabel,

	CE_ProgressBarGroove,
	CE_ProgressBarContents,
	CE_ProgressBarLabel,

	CE_PopupMenuItem,
	CE_MenuBarItem,

	CE_ToolButtonLabel,
	CE_PopupMenuScroller,

	// do not add any values below/greater than this
	CE_CustomBase =		0xf0000000
    };

    virtual void drawControl( ControlElement element,
			      QPainter *p,
			      const QWidget *widget,
			      const QRect &r,
			      const QColorGroup &cg,
			      SFlags how = Style_Default,
			      const QStyleOption& = QStyleOption::Default ) const = 0;
    virtual void drawControlMask( ControlElement element,
				  QPainter *p,
				  const QWidget *widget,
				  const QRect &r,
				  const QStyleOption& = QStyleOption::Default ) const = 0;

    enum SubRect {
	SR_PushButtonContents,
	SR_PushButtonFocusRect,

	SR_CheckBoxIndicator,
	SR_CheckBoxContents,
	SR_CheckBoxFocusRect,

	SR_RadioButtonIndicator,
	SR_RadioButtonContents,
	SR_RadioButtonFocusRect,

	SR_ComboBoxFocusRect,

	SR_SliderFocusRect,

	SR_DockWindowHandleRect,

	SR_ProgressBarGroove,
	SR_ProgressBarContents,
	SR_ProgressBarLabel,

	SR_ToolButtonContents,

	// do not add any values below/greater than this
	SR_CustomBase =		0xf0000000
    };

    virtual QRect subRect( SubRect r, const QWidget *widget ) const = 0;


    enum ComplexControl{
	CC_SpinWidget,
	CC_ComboBox,
	CC_ScrollBar,
	CC_Slider,
	CC_ToolButton,
	CC_TitleBar,
	CC_ListView,

	// do not add any values below/greater than this
	CC_CustomBase =		0xf0000000
    };

    enum SubControl {
	SC_None =			0x00000000,

	SC_ScrollBarAddLine =		0x00000001,
	SC_ScrollBarSubLine =		0x00000002,
	SC_ScrollBarAddPage =		0x00000004,
	SC_ScrollBarSubPage =		0x00000008,
	SC_ScrollBarFirst =		0x00000010,
	SC_ScrollBarLast =		0x00000020,
	SC_ScrollBarSlider =		0x00000040,
	SC_ScrollBarGroove =		0x00000080,

	SC_SpinWidgetUp =		0x00000001,
	SC_SpinWidgetDown =		0x00000002,
	SC_SpinWidgetFrame =		0x00000004,
	SC_SpinWidgetEditField =	0x00000008,
	SC_SpinWidgetButtonField =	0x00000010,

	SC_ComboBoxFrame =		0x00000001,
	SC_ComboBoxEditField =		0x00000002,
	SC_ComboBoxArrow =		0x00000004,

	SC_SliderGroove =		0x00000001,
	SC_SliderHandle = 		0x00000002,
	SC_SliderTickmarks = 		0x00000004,

	SC_ToolButton =			0x00000001,
	SC_ToolButtonMenu =		0x00000002,

	SC_TitleBarLabel =		0x00000001,
	SC_TitleBarSysMenu =		0x00000002,
	SC_TitleBarMinButton =		0x00000004,
	SC_TitleBarMaxButton =		0x00000008,
	SC_TitleBarCloseButton =	0x00000010,
	SC_TitleBarNormalButton =	0x00000020,
	SC_TitleBarShadeButton =	0x00000040,
	SC_TitleBarUnshadeButton =	0x00000080,

	SC_ListView =			0x00000001,
	SC_ListViewBranch =		0x00000002,
	SC_ListViewExpand =		0x00000004,

	SC_All =			0xffffffff
    };
    typedef uint SCFlags;


    virtual void drawComplexControl( ComplexControl control,
				     QPainter *p,
				     const QWidget *widget,
				     const QRect &r,
				     const QColorGroup &cg,
				     SFlags how = Style_Default,
				     SCFlags sub = SC_All,
				     SCFlags subActive = SC_None,
				     const QStyleOption& = QStyleOption::Default ) const = 0;
    virtual void drawComplexControlMask( ComplexControl control,
					 QPainter *p,
					 const QWidget *widget,
					 const QRect &r,
					 const QStyleOption& = QStyleOption::Default ) const = 0;

    virtual QRect querySubControlMetrics( ComplexControl control,
					  const QWidget *widget,
					  SubControl sc,
					  const QStyleOption& = QStyleOption::Default ) const = 0;
    virtual SubControl querySubControl( ComplexControl control,
					const QWidget *widget,
					const QPoint &pos,
					const QStyleOption& = QStyleOption::Default ) const = 0;


    enum PixelMetric {
	PM_ButtonMargin,
	PM_ButtonDefaultIndicator,
	PM_MenuButtonIndicator,
	PM_ButtonShiftHorizontal,
	PM_ButtonShiftVertical,

	PM_DefaultFrameWidth,
	PM_SpinBoxFrameWidth,

	PM_MaximumDragDistance,

	PM_ScrollBarExtent,
	PM_ScrollBarSliderMin,

	PM_SliderThickness,	       	// total slider thickness
	PM_SliderControlThickness,    	// thickness of the business part
	PM_SliderLength,		// total length of slider
	PM_SliderTickmarkOffset,	//
	PM_SliderSpaceAvailable,	// available space for slider to move

	PM_DockWindowSeparatorExtent,
	PM_DockWindowHandleExtent,
	PM_DockWindowFrameWidth,

	PM_MenuBarFrameWidth,

	PM_TabBarTabOverlap,
	PM_TabBarTabHSpace,
	PM_TabBarTabVSpace,
	PM_TabBarBaseHeight,
	PM_TabBarBaseOverlap,

	PM_ProgressBarChunkWidth,

	PM_SplitterWidth,
	PM_TitleBarHeight,

	PM_IndicatorWidth,
	PM_IndicatorHeight,
	PM_ExclusiveIndicatorWidth,
	PM_ExclusiveIndicatorHeight,
	PM_PopupMenuScrollerHeight,

	// do not add any values below/greater than this
	PM_CustomBase =		0xf0000000
    };

    virtual int pixelMetric( PixelMetric metric,
			     const QWidget *widget = 0 ) const = 0;


    enum ContentsType {
	CT_PushButton,
	CT_CheckBox,
	CT_RadioButton,
	CT_ToolButton,
	CT_ComboBox,
	CT_Splitter,
	CT_DockWindow,
	CT_ProgressBar,
	CT_PopupMenuItem,

	// do not add any values below/greater than this
	CT_CustomBase =		0xf0000000
    };

    virtual QSize sizeFromContents( ContentsType contents,
				    const QWidget *widget,
				    const QSize &contentsSize,
				    const QStyleOption& = QStyleOption::Default ) const = 0;

    enum StyleHint  {
	// ...
	// the general hints
	// ...
       	// disabled text should be etched, ala Windows
	SH_EtchDisabledText,

	// the GUI style enum, argh!
	SH_GUIStyle,

	// ...
	// widget specific hints
	// ...
	SH_ScrollBar_BackgroundMode,
	SH_ScrollBar_MiddleClickAbsolutePosition,
	SH_ScrollBar_ScrollWhenPointerLeavesControl,

	// QEvent::Type - which mouse event to select a tab
	SH_TabBar_SelectMouseType,

	SH_TabBar_Alignment,

	SH_Header_ArrowAlignment,

	// bool - sliders snap to values while moving, ala Windows
	SH_Slider_SnapToValue,

	// bool - key presses handled in a sloppy manner - ie. left on a vertical
	// slider subtracts a line
	SH_Slider_SloppyKeyEvents,

	// bool - center button on progress dialogs, ala Motif, else right aligned
	// perhaps this should be a Qt::Alignment value
	SH_ProgressDialog_CenterCancelButton,

	// Qt::AlignmentFlags - text label alignment in progress dialogs
	// Center on windows, Auto|VCenter otherwize
	SH_ProgressDialog_TextLabelAlignment,

	// bool - right align buttons on print dialog, ala Windows
	SH_PrintDialog_RightAlignButtons,

	// bool - 1 or 2 pixel space between the menubar and the dockarea, ala Windows
	// this *REALLY* needs a better name
	SH_MainWindow_SpaceBelowMenuBar,

	// bool - select the text in the line edit about the listbox when selecting
	// an item from the listbox, or when the line edit receives focus, ala Windows
	SH_FontDialog_SelectAssociatedText,

	// bool - allows disabled menu items to be active
	SH_PopupMenu_AllowActiveAndDisabled,

	// bool - pressing space activates item, ala Motif
	SH_PopupMenu_SpaceActivatesItem,

	// int - number of milliseconds to wait before opening a submenu
	// 256 on windows, 96 on motif
	SH_PopupMenu_SubMenuPopupDelay,

	// bool - should scrollviews draw their frame only around contents (ala Motif),
	// or around contents, scrollbars and corner widgets (ala Windows) ?
	SH_ScrollView_FrameOnlyAroundContents,

	// bool - menubars items are navigatable by pressing alt, followed by using
	// the arrow keys to select the desired item
	SH_MenuBar_AltKeyNavigation,

	// bool - mouse tracking in combobox dropdown lists
	SH_ComboBox_ListMouseTracking,

	// bool - mouse tracking in popupmenus
	SH_PopupMenu_MouseTracking,

	// bool - mouse tracking in menubars
	SH_MenuBar_MouseTracking,

	// bool - gray out selected items when loosing focus
	SH_ItemView_ChangeHighlightOnFocus,

	// bool - supports shared activation among modeless widgets
	SH_Widget_ShareActivation,

	// bool - workspace should just maximize the client area
	SH_Workspace_FillSpaceOnMaximize,

	// bool - supports popup menu comboboxes
	SH_ComboBox_Popup, 

	// bool - titlebar has no border
	SH_TitleBar_NoBorder,

	// bool - stop scrollbar at mouse
	SH_ScrollBar_StopMouseOverSlider,

	//bool - blink cursort with selected text
	SH_BlinkCursorWhenTextSelected,

	//bool - richtext selections extend the full width of the docuemnt
	SH_RichText_FullWidthSelection,

	//bool - popupmenu supports scrolling instead of multicolumn mode
	SH_PopupMenu_Scrollable,

	// do not add any values below/greater than this
	SH_CustomBase =		0xf0000000
    };

    virtual int styleHint( StyleHint stylehint,
			   const QWidget *widget = 0,
			   const QStyleOption& = QStyleOption::Default,
			   QStyleHintReturn* returnData = 0
			   ) const = 0;


    enum StylePixmap {
	SP_TitleBarMinButton,
	SP_TitleBarMaxButton,
	SP_TitleBarCloseButton,
	SP_TitleBarNormalButton,
	SP_TitleBarShadeButton,
	SP_TitleBarUnshadeButton,
	SP_DockWindowCloseButton,
	SP_MessageBoxInformation,
	SP_MessageBoxWarning,
	SP_MessageBoxCritical,

	// do not add any values below/greater than this
	SP_CustomBase =		0xf0000000
    };

    virtual QPixmap stylePixmap( StylePixmap stylepixmap,
				 const QWidget *widget = 0,
				 const QStyleOption& = QStyleOption::Default ) const = 0;


    static QRect visualRect( const QRect &logical, const QWidget *w );

    static QRect visualRect( const QRect &logical, const QRect &bounding );




    // Old 2.x QStyle API

#ifndef QT_NO_COMPAT
    int defaultFrameWidth() const
    {
	return pixelMetric( PM_DefaultFrameWidth );
    }
    void tabbarMetrics( const QWidget* t,
			int& hf, int& vf, int& ov ) const
    {
	hf = pixelMetric( PM_TabBarTabHSpace, t );
	vf = pixelMetric( PM_TabBarTabVSpace, t );
	ov = pixelMetric( PM_TabBarBaseOverlap, t );
    }
    QSize scrollBarExtent() const
    {
	return QSize(pixelMetric(PM_ScrollBarExtent),
		     pixelMetric(PM_ScrollBarExtent));
    }
#endif


private:
    QStylePrivate * d;

#if defined(Q_DISABLE_COPY)
    QStyle( const QStyle & );
    QStyle& operator=( const QStyle & );
#endif
};

#endif // QT_NO_STYLE
#endif // QSTYLE_H
