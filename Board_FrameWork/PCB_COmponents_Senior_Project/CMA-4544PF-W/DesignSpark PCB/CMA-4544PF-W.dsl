SamacSys ECAD Model
233254/67790/2.32/2/3/Microphone

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c120_h70"
		(holeDiam 0.7)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.2) (shapeHeight 1.2))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.2) (shapeHeight 1.2))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "CMA-4544PF-W" (originalName "CMA-4544PF-W")
		(multiLayer
			(pad (padNum 1) (padStyleRef c120_h70) (pt 2, 1.27) (rotation 90))
			(pad (padNum 2) (padStyleRef c120_h70) (pt 2, -1.27) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt -3.722, 1.966) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 0, 0) (radius 9.85) (startAngle 0.0) (sweepAngle 0.0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 0, 0) (radius 9.85) (startAngle 180.0) (sweepAngle 180.0) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(arc (pt 0, 0) (radius 9.85) (startAngle 0.0) (sweepAngle 0.0) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(arc (pt 0, 0) (radius 9.85) (startAngle 180.0) (sweepAngle 180.0) (width 0.2))
		)
	)
	(symbolDef "CMA-4544PF-W" (originalName "CMA-4544PF-W")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 800 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 570 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -100 mils) (width 6 mils))
		(line (pt 600 mils -100 mils) (pt 200 mils -100 mils) (width 6 mils))
		(line (pt 200 mils -100 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "CMA-4544PF-W" (originalName "CMA-4544PF-W") (compHeader (numPins 2) (numParts 1) (refDesPrefix MK)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "CMA-4544PF-W"))
		(attachedPattern (patternNum 1) (patternName "CMA-4544PF-W")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Manufacturer_Name" "CUI")
		(attr "Manufacturer_Part_Number" "CMA-4544PF-W")
		(attr "RS Part Number" "")
		(attr "RS Price/Stock" "")
		(attr "Arrow Part Number" "CMA-4544PF-W")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/cma-4544pf-w/cui-inc")
		(attr "Description" "ELECTRET CONDENSER MICROPHONE")
		(attr "Datasheet Link" "http://www.cui.com/product/resource/cma-4544pf-w.pdf")
	)

)
