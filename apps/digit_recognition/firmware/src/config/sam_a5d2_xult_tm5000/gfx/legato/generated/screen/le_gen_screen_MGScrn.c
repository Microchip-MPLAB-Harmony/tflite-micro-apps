#include "gfx/legato/generated/screen/le_gen_screen_MGScrn.h"

// screen member widget declarations
static leWidget* root0;
static leWidget* root1;
static leWidget* root2;

leWidget* MGScrn_PanelWidget0;
leImageWidget* MGScrn_ImageWidget0;
leDrawSurfaceWidget* MGScrn_DrawSurfaceWidget0;
leImageWidget* MGScrn_GestureImageWidget;
leImageWidget* MGScrn_ImageWidget1;
leLabelWidget* MGScrn_LabelWidget0;
leWidget* MGScrn_PanelWidget1;
leWidget* MGScrn_PanelWidget2;
leWidget* MGScrn_PanelWidget3;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_MGScrn(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_MGScrn(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 800, 480);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGBA_8888);

    // layer 1
    root1 = leWidget_New();
    root1->fn->setSize(root1, 800, 480);
    root1->fn->setBackgroundType(root1, LE_WIDGET_BACKGROUND_NONE);
    root1->fn->setMargins(root1, 0, 0, 0, 0);
    root1->flags |= LE_WIDGET_IGNOREEVENTS;
    root1->flags |= LE_WIDGET_IGNOREPICK;

    leAddRootWidget(root1, 1);
    leSetLayerColorMode(1, LE_COLOR_MODE_RGBA_8888);

    // layer 2
    root2 = leWidget_New();
    root2->fn->setSize(root2, 800, 480);
    root2->fn->setBackgroundType(root2, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->setMargins(root2, 0, 0, 0, 0);
    root2->flags |= LE_WIDGET_IGNOREEVENTS;
    root2->flags |= LE_WIDGET_IGNOREPICK;

    MGScrn_PanelWidget0 = leWidget_New();
    MGScrn_PanelWidget0->fn->setPosition(MGScrn_PanelWidget0, 0, 0);
    MGScrn_PanelWidget0->fn->setSize(MGScrn_PanelWidget0, 300, 480);
    MGScrn_PanelWidget0->fn->setScheme(MGScrn_PanelWidget0, &WhiteBackGroundScheme);
    root2->fn->addChild(root2, (leWidget*)MGScrn_PanelWidget0);

    MGScrn_ImageWidget0 = leImageWidget_New();
    MGScrn_ImageWidget0->fn->setPosition(MGScrn_ImageWidget0, 11, 11);
    MGScrn_ImageWidget0->fn->setSize(MGScrn_ImageWidget0, 152, 40);
    MGScrn_ImageWidget0->fn->setBackgroundType(MGScrn_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_ImageWidget0->fn->setBorderType(MGScrn_ImageWidget0, LE_WIDGET_BORDER_NONE);
    MGScrn_ImageWidget0->fn->setImage(MGScrn_ImageWidget0, (leImage*)&mchpLogo_light);
    root2->fn->addChild(root2, (leWidget*)MGScrn_ImageWidget0);

    MGScrn_DrawSurfaceWidget0 = leDrawSurfaceWidget_New();
    MGScrn_DrawSurfaceWidget0->fn->setPosition(MGScrn_DrawSurfaceWidget0, 300, 16);
    MGScrn_DrawSurfaceWidget0->fn->setSize(MGScrn_DrawSurfaceWidget0, 448, 448);
    MGScrn_DrawSurfaceWidget0->fn->setScheme(MGScrn_DrawSurfaceWidget0, &WhiteBackGroundScheme);
    MGScrn_DrawSurfaceWidget0->fn->setBackgroundType(MGScrn_DrawSurfaceWidget0, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_DrawSurfaceWidget0->fn->setBorderType(MGScrn_DrawSurfaceWidget0, LE_WIDGET_BORDER_LINE);
    MGScrn_DrawSurfaceWidget0->fn->setDrawCallback(MGScrn_DrawSurfaceWidget0, event_MGScrn_DrawSurfaceWidget0_OnDraw);
    root2->fn->addChild(root2, (leWidget*)MGScrn_DrawSurfaceWidget0);

    MGScrn_GestureImageWidget = leImageWidget_New();
    MGScrn_GestureImageWidget->fn->setPosition(MGScrn_GestureImageWidget, 300, 16);
    MGScrn_GestureImageWidget->fn->setSize(MGScrn_GestureImageWidget, 448, 448);
    MGScrn_GestureImageWidget->fn->setEnabled(MGScrn_GestureImageWidget, LE_FALSE);
    MGScrn_GestureImageWidget->fn->setScheme(MGScrn_GestureImageWidget, &WhiteBackGroundScheme);
    MGScrn_GestureImageWidget->fn->setBorderType(MGScrn_GestureImageWidget, LE_WIDGET_BORDER_LINE);
    root2->fn->addChild(root2, (leWidget*)MGScrn_GestureImageWidget);

    MGScrn_ImageWidget1 = leImageWidget_New();
    MGScrn_ImageWidget1->fn->setPosition(MGScrn_ImageWidget1, 96, 198);
    MGScrn_ImageWidget1->fn->setSize(MGScrn_ImageWidget1, 99, 116);
    MGScrn_ImageWidget1->fn->setBackgroundType(MGScrn_ImageWidget1, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_ImageWidget1->fn->setBorderType(MGScrn_ImageWidget1, LE_WIDGET_BORDER_NONE);
    MGScrn_ImageWidget1->fn->setImage(MGScrn_ImageWidget1, (leImage*)&MLlogo);
    root2->fn->addChild(root2, (leWidget*)MGScrn_ImageWidget1);

    MGScrn_LabelWidget0 = leLabelWidget_New();
    MGScrn_LabelWidget0->fn->setPosition(MGScrn_LabelWidget0, 64, 157);
    MGScrn_LabelWidget0->fn->setSize(MGScrn_LabelWidget0, 180, 38);
    MGScrn_LabelWidget0->fn->setBackgroundType(MGScrn_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    MGScrn_LabelWidget0->fn->setString(MGScrn_LabelWidget0, (leString*)&string_DigitRecognition);
    root2->fn->addChild(root2, (leWidget*)MGScrn_LabelWidget0);

    MGScrn_PanelWidget1 = leWidget_New();
    MGScrn_PanelWidget1->fn->setPosition(MGScrn_PanelWidget1, 300, 0);
    MGScrn_PanelWidget1->fn->setSize(MGScrn_PanelWidget1, 500, 16);
    MGScrn_PanelWidget1->fn->setScheme(MGScrn_PanelWidget1, &WhiteBackGroundScheme);
    root2->fn->addChild(root2, (leWidget*)MGScrn_PanelWidget1);

    MGScrn_PanelWidget2 = leWidget_New();
    MGScrn_PanelWidget2->fn->setPosition(MGScrn_PanelWidget2, 748, 0);
    MGScrn_PanelWidget2->fn->setSize(MGScrn_PanelWidget2, 52, 480);
    MGScrn_PanelWidget2->fn->setScheme(MGScrn_PanelWidget2, &WhiteBackGroundScheme);
    root2->fn->addChild(root2, (leWidget*)MGScrn_PanelWidget2);

    MGScrn_PanelWidget3 = leWidget_New();
    MGScrn_PanelWidget3->fn->setPosition(MGScrn_PanelWidget3, 300, 464);
    MGScrn_PanelWidget3->fn->setSize(MGScrn_PanelWidget3, 500, 16);
    MGScrn_PanelWidget3->fn->setScheme(MGScrn_PanelWidget3, &WhiteBackGroundScheme);
    root2->fn->addChild(root2, (leWidget*)MGScrn_PanelWidget3);

    leAddRootWidget(root2, 2);
    leSetLayerColorMode(2, LE_COLOR_MODE_RGBA_8888);

    MGScrn_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_MGScrn(void)
{
    root0->fn->setSize(root0, root0->parent->rect.width, root0->parent->rect.height);
    root1->fn->setSize(root1, root1->parent->rect.width, root1->parent->rect.height);
    root2->fn->setSize(root2, root2->parent->rect.width, root2->parent->rect.height);

    MGScrn_OnUpdate(); // raise event
}

void screenHide_MGScrn(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    leRemoveRootWidget(root1, 1);
    leWidget_Delete(root1);
    root1 = NULL;

    leRemoveRootWidget(root2, 2);
    leWidget_Delete(root2);
    root2 = NULL;

    MGScrn_PanelWidget0 = NULL;
    MGScrn_ImageWidget0 = NULL;
    MGScrn_DrawSurfaceWidget0 = NULL;
    MGScrn_GestureImageWidget = NULL;
    MGScrn_ImageWidget1 = NULL;
    MGScrn_LabelWidget0 = NULL;
    MGScrn_PanelWidget1 = NULL;
    MGScrn_PanelWidget2 = NULL;
    MGScrn_PanelWidget3 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_MGScrn(void)
{
    if(initialized == LE_FALSE)
        return;

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
        case 1:
        {
            return root1;
        }
        case 2:
        {
            return root2;
        }
        default:
        {
            return NULL;
        }
    }
}

