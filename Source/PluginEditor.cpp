/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DpidetectorAudioProcessorEditor::DpidetectorAudioProcessorEditor (DpidetectorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    zoomMenu.addItem("100%", 1);
    zoomMenu.addItem("150%", 2);
    zoomMenu.setSelectedId(1);
    addAndMakeVisible(&zoomMenu);
    zoomMenu.addListener(this);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    initWidth = 800;
    initHeight = 640;
    setSize (initWidth, initHeight);
}

DpidetectorAudioProcessorEditor::~DpidetectorAudioProcessorEditor()
{
}

//==============================================================================
void DpidetectorAudioProcessorEditor::paint (Graphics& g)
{
    int width = getWidth();
    int height = getHeight();
    int offset = 10;
    int centerX = width / 2;
    int centerY = height / 2;
    
    int sizePosY = centerY - 100;
    
    int textWidth = 400;
    
    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    g.fillAll (Colours::grey);
    for (int i = 0; i < 10; i++) {
        g.drawRect(i * offset, i * offset, width - 2 * i * offset, height - 2 * i * offset, 1);
    }
    g.drawText("Plugin Size: " + std::to_string(width) + " x " + std::to_string(height), centerX - textWidth / 2, sizePosY, textWidth, 20, Justification::centred);
    
    int offsetY = 20;
    for (int i = 0; i < dpis.size(); ++i)
    {
        int yPos = sizePosY + offsetY;
        g.drawText("Display " + std::to_string(i) + "  -  " + "DPI: " + std::to_string(dpis[i]) + "    Scale: " + std::to_string(scales[i]), centerX - textWidth / 2, yPos, textWidth, 20, Justification::centred);
        offsetY += 20;
    }
   
    
}

void DpidetectorAudioProcessorEditor::comboBoxChanged (ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &zoomMenu)
    {
        auto selection = std::stoi(zoomMenu.getText().removeCharacters("%").toStdString()) / 100.f;
        
        setSize(initWidth * selection, initHeight * selection);
    }
}

void DpidetectorAudioProcessorEditor::resized()
{
    zoomMenu.setBoundsRelative(600.f / 800.f, 100.f / 640.f, 80.f / 800.f, 35.f / 640.f);
    
    dpis.clear();
    scales.clear();
    
    auto allDisplays = Desktop::getInstance().getDisplays().displays;
    for (int iDisplay = 0; iDisplay < allDisplays.size(); ++iDisplay)
    {
        dpis.push_back(allDisplays[iDisplay].dpi);
        scales.push_back(allDisplays[iDisplay].scale);
    }
    
    /** The DPI of the display.
     This is the number of physical pixels per inch. To get the number of logical
     pixels per inch, divide this by the Display::scale value.
     */
    //dpi = Desktop::getInstance().getDisplays().getMainDisplay().dpi;
    
    /** This is the scale-factor of this display.
     If you create a component with size 1x1, this scale factor indicates the actual
     size of the component in terms of physical pixels.
     For higher-resolution displays, it may be a value greater than 1.0
     */
    //scale = Desktop::getInstance().getDisplays().getMainDisplay().scale;
}
