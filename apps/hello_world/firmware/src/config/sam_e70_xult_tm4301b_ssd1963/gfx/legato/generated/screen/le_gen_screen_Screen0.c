#include "gfx/legato/generated/screen/le_gen_screen_Screen0.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen0_BackgroundPanel;
leImageWidget* Screen0_mchpLogo;
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
    root0->fn->setSize(root0, 480, 272);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen0_BackgroundPanel = leWidget_New();
    Screen0_BackgroundPanel->fn->setPosition(Screen0_BackgroundPanel, 0, 0);
    Screen0_BackgroundPanel->fn->setSize(Screen0_BackgroundPanel, 480, 272);
    Screen0_BackgroundPanel->fn->setScheme(Screen0_BackgroundPanel, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_BackgroundPanel);

    Screen0_mchpLogo = leImageWidget_New();
    Screen0_mchpLogo->fn->setPosition(Screen0_mchpLogo, 5, 5);
    Screen0_mchpLogo->fn->setSize(Screen0_mchpLogo, 120, 28);
    Screen0_mchpLogo->fn->setBackgroundType(Screen0_mchpLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen0_mchpLogo->fn->setBorderType(Screen0_mchpLogo, LE_WIDGET_BORDER_NONE);
    Screen0_mchpLogo->fn->setImage(Screen0_mchpLogo, (leImage*)&mchpLogo_small);
    root0->fn->addChild(root0, (leWidget*)Screen0_mchpLogo);

    Screen0_DrawSurfaceWidget0 = leDrawSurfaceWidget_New();
    Screen0_DrawSurfaceWidget0->fn->setPosition(Screen0_DrawSurfaceWidget0, 100, 50);
    Screen0_DrawSurfaceWidget0->fn->setSize(Screen0_DrawSurfaceWidget0, 300, 200);
    Screen0_DrawSurfaceWidget0->fn->setDrawCallback(Screen0_DrawSurfaceWidget0, event_Screen0_DrawSurfaceWidget0_OnDraw);
    root0->fn->addChild(root0, (leWidget*)Screen0_DrawSurfaceWidget0);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen0(void)
{
    root0->fn->setSize(root0, root0->parent->rect.width, root0->parent->rect.height);
}

void screenHide_Screen0(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen0_BackgroundPanel = NULL;
    Screen0_mchpLogo = NULL;
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
        default:
        {
            return NULL;
        }
    }
}

