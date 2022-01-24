#include "gfx/legato/generated/screen/le_gen_screen_MGScrn.h"

// screen member widget declarations
static leWidget* root0;

leWidget* MGScrn_PanelWidget3;
leWidget* MGScrn_PanelWidget2;
leWidget* MGScrn_PanelWidget1;
leWidget* MGScrn_PanelWidget0;
leDrawSurfaceWidget* MGScrn_DrawSurfaceWidget0;
leImageWidget* MGScrn_GestureImageWidget;
leLabelWidget* MGScrn_DrawInstructionLabel;
leImageWidget* MGScrn_ImageWidget0;
leLabelWidget* MGScrn_LabelWidget0;
leImageWidget* MGScrn_ImageWidget1;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_MGScrn(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 480, 272);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    MGScrn_PanelWidget3 = leWidget_New();
    MGScrn_PanelWidget3->fn->setPosition(MGScrn_PanelWidget3, 424, 0);
    MGScrn_PanelWidget3->fn->setSize(MGScrn_PanelWidget3, 56, 272);
    MGScrn_PanelWidget3->fn->setScheme(MGScrn_PanelWidget3, &MGScheme);
    root0->fn->addChild(root0, (leWidget*)MGScrn_PanelWidget3);

    MGScrn_PanelWidget2 = leWidget_New();
    MGScrn_PanelWidget2->fn->setPosition(MGScrn_PanelWidget2, 0, 254);
    MGScrn_PanelWidget2->fn->setSize(MGScrn_PanelWidget2, 480, 18);
    MGScrn_PanelWidget2->fn->setScheme(MGScrn_PanelWidget2, &MGScheme);
    root0->fn->addChild(root0, (leWidget*)MGScrn_PanelWidget2);

    MGScrn_PanelWidget1 = leWidget_New();
    MGScrn_PanelWidget1->fn->setPosition(MGScrn_PanelWidget1, 0, 0);
    MGScrn_PanelWidget1->fn->setSize(MGScrn_PanelWidget1, 480, 30);
    MGScrn_PanelWidget1->fn->setScheme(MGScrn_PanelWidget1, &MGScheme);
    root0->fn->addChild(root0, (leWidget*)MGScrn_PanelWidget1);

    MGScrn_PanelWidget0 = leWidget_New();
    MGScrn_PanelWidget0->fn->setPosition(MGScrn_PanelWidget0, 0, 0);
    MGScrn_PanelWidget0->fn->setSize(MGScrn_PanelWidget0, 200, 272);
    MGScrn_PanelWidget0->fn->setScheme(MGScrn_PanelWidget0, &MGScheme);
    root0->fn->addChild(root0, (leWidget*)MGScrn_PanelWidget0);

    MGScrn_DrawSurfaceWidget0 = leDrawSurfaceWidget_New();
    MGScrn_DrawSurfaceWidget0->fn->setPosition(MGScrn_DrawSurfaceWidget0, 200, 30);
    MGScrn_DrawSurfaceWidget0->fn->setSize(MGScrn_DrawSurfaceWidget0, 224, 224);
    MGScrn_DrawSurfaceWidget0->fn->setScheme(MGScrn_DrawSurfaceWidget0, &WhiteBackgroundScheme);
    MGScrn_DrawSurfaceWidget0->fn->setBackgroundType(MGScrn_DrawSurfaceWidget0, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_DrawSurfaceWidget0->fn->setBorderType(MGScrn_DrawSurfaceWidget0, LE_WIDGET_BORDER_LINE);
    MGScrn_DrawSurfaceWidget0->fn->setDrawCallback(MGScrn_DrawSurfaceWidget0, event_MGScrn_DrawSurfaceWidget0_OnDraw);
    root0->fn->addChild(root0, (leWidget*)MGScrn_DrawSurfaceWidget0);

    MGScrn_GestureImageWidget = leImageWidget_New();
    MGScrn_GestureImageWidget->fn->setPosition(MGScrn_GestureImageWidget, 200, 30);
    MGScrn_GestureImageWidget->fn->setSize(MGScrn_GestureImageWidget, 224, 224);
    MGScrn_GestureImageWidget->fn->setEnabled(MGScrn_GestureImageWidget, LE_FALSE);
    MGScrn_GestureImageWidget->fn->setScheme(MGScrn_GestureImageWidget, &WhiteBackgroundScheme);
    MGScrn_GestureImageWidget->fn->setBorderType(MGScrn_GestureImageWidget, LE_WIDGET_BORDER_LINE);
    MGScrn_GestureImageWidget->fn->setImage(MGScrn_GestureImageWidget, (leImage*)&Microchip_logo_150x30);
    root0->fn->addChild(root0, (leWidget*)MGScrn_GestureImageWidget);

    MGScrn_DrawInstructionLabel = leLabelWidget_New();
    MGScrn_DrawInstructionLabel->fn->setPosition(MGScrn_DrawInstructionLabel, 200, 0);
    MGScrn_DrawInstructionLabel->fn->setSize(MGScrn_DrawInstructionLabel, 224, 25);
    MGScrn_DrawInstructionLabel->fn->setEnabled(MGScrn_DrawInstructionLabel, LE_FALSE);
    MGScrn_DrawInstructionLabel->fn->setScheme(MGScrn_DrawInstructionLabel, &MGScheme);
    MGScrn_DrawInstructionLabel->fn->setHAlignment(MGScrn_DrawInstructionLabel, LE_HALIGN_CENTER);
    MGScrn_DrawInstructionLabel->fn->setVAlignment(MGScrn_DrawInstructionLabel, LE_VALIGN_TOP);
    MGScrn_DrawInstructionLabel->fn->setString(MGScrn_DrawInstructionLabel, (leString*)&string_StartDrawing);
    root0->fn->addChild(root0, (leWidget*)MGScrn_DrawInstructionLabel);

    MGScrn_ImageWidget0 = leImageWidget_New();
    MGScrn_ImageWidget0->fn->setPosition(MGScrn_ImageWidget0, 21, 13);
    MGScrn_ImageWidget0->fn->setSize(MGScrn_ImageWidget0, 154, 32);
    MGScrn_ImageWidget0->fn->setBackgroundType(MGScrn_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_ImageWidget0->fn->setBorderType(MGScrn_ImageWidget0, LE_WIDGET_BORDER_NONE);
    MGScrn_ImageWidget0->fn->setImage(MGScrn_ImageWidget0, (leImage*)&Microchip_logo_150x30);
    root0->fn->addChild(root0, (leWidget*)MGScrn_ImageWidget0);

    MGScrn_LabelWidget0 = leLabelWidget_New();
    MGScrn_LabelWidget0->fn->setPosition(MGScrn_LabelWidget0, 23, 63);
    MGScrn_LabelWidget0->fn->setSize(MGScrn_LabelWidget0, 170, 25);
    MGScrn_LabelWidget0->fn->setBackgroundType(MGScrn_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_LabelWidget0->fn->setString(MGScrn_LabelWidget0, (leString*)&string_TouchTitle);
    root0->fn->addChild(root0, (leWidget*)MGScrn_LabelWidget0);

    MGScrn_ImageWidget1 = leImageWidget_New();
    MGScrn_ImageWidget1->fn->setPosition(MGScrn_ImageWidget1, 47, 101);
    MGScrn_ImageWidget1->fn->setBackgroundType(MGScrn_ImageWidget1, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_ImageWidget1->fn->setBorderType(MGScrn_ImageWidget1, LE_WIDGET_BORDER_NONE);
    MGScrn_ImageWidget1->fn->setImage(MGScrn_ImageWidget1, (leImage*)&TouchML);
    root0->fn->addChild(root0, (leWidget*)MGScrn_ImageWidget1);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_MGScrn(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    MGScrn_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_MGScrn(void)
{
    root0->fn->setSize(root0, root0->parent->rect.width, root0->parent->rect.height);

    MGScrn_OnUpdate(); // raise event
}

void screenHide_MGScrn(void)
{
    MGScrn_OnHide(); // raise event

    showing = LE_FALSE;
}

void screenDestroy_MGScrn(void)
{
    if(initialized == LE_FALSE)
        return;

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    MGScrn_PanelWidget3 = NULL;
    MGScrn_PanelWidget2 = NULL;
    MGScrn_PanelWidget1 = NULL;
    MGScrn_PanelWidget0 = NULL;
    MGScrn_DrawSurfaceWidget0 = NULL;
    MGScrn_GestureImageWidget = NULL;
    MGScrn_DrawInstructionLabel = NULL;
    MGScrn_ImageWidget0 = NULL;
    MGScrn_LabelWidget0 = NULL;
    MGScrn_ImageWidget1 = NULL;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_MGScrn(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}

