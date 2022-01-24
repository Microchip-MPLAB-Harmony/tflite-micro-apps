#include "gfx/legato/generated/screen/le_gen_screen_Screen0.h"

// screen member widget declarations
static leWidget* root0;
static leWidget* root1;
static leWidget* root2;

leWidget* Screen0_default_Layer0_FillPanel;
leImageWidget* Screen0_ImageWidget0;
leDrawSurfaceWidget* Screen0_DrawSurfaceWidget0;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen0(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen0(void)
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

    Screen0_default_Layer0_FillPanel = leWidget_New();
    Screen0_default_Layer0_FillPanel->fn->setPosition(Screen0_default_Layer0_FillPanel, 0, 0);
    Screen0_default_Layer0_FillPanel->fn->setSize(Screen0_default_Layer0_FillPanel, 800, 480);
    Screen0_default_Layer0_FillPanel->fn->setScheme(Screen0_default_Layer0_FillPanel, &LayerScheme);
    root2->fn->addChild(root2, (leWidget*)Screen0_default_Layer0_FillPanel);

    Screen0_ImageWidget0 = leImageWidget_New();
    Screen0_ImageWidget0->fn->setPosition(Screen0_ImageWidget0, 11, 11);
    Screen0_ImageWidget0->fn->setSize(Screen0_ImageWidget0, 152, 40);
    Screen0_ImageWidget0->fn->setBackgroundType(Screen0_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    Screen0_ImageWidget0->fn->setBorderType(Screen0_ImageWidget0, LE_WIDGET_BORDER_NONE);
    Screen0_ImageWidget0->fn->setImage(Screen0_ImageWidget0, (leImage*)&mchpLogo_light);
    root2->fn->addChild(root2, (leWidget*)Screen0_ImageWidget0);

    Screen0_DrawSurfaceWidget0 = leDrawSurfaceWidget_New();
    Screen0_DrawSurfaceWidget0->fn->setPosition(Screen0_DrawSurfaceWidget0, 100, 80);
    Screen0_DrawSurfaceWidget0->fn->setSize(Screen0_DrawSurfaceWidget0, 600, 380);
    Screen0_DrawSurfaceWidget0->fn->setDrawCallback(Screen0_DrawSurfaceWidget0, event_Screen0_DrawSurfaceWidget0_OnDraw);
    root2->fn->addChild(root2, (leWidget*)Screen0_DrawSurfaceWidget0);

    leAddRootWidget(root2, 2);
    leSetLayerColorMode(2, LE_COLOR_MODE_RGBA_8888);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen0(void)
{
    root0->fn->setSize(root0, root0->parent->rect.width, root0->parent->rect.height);
    root1->fn->setSize(root1, root1->parent->rect.width, root1->parent->rect.height);
    root2->fn->setSize(root2, root2->parent->rect.width, root2->parent->rect.height);
}

void screenHide_Screen0(void)
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

    Screen0_default_Layer0_FillPanel = NULL;
    Screen0_ImageWidget0 = NULL;
    Screen0_DrawSurfaceWidget0 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen0(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen0(uint32_t lyrIdx)
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

