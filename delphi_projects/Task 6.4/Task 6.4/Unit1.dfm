object Form1: TForm1
  Left = 688
  Top = 169
  Width = 839
  Height = 394
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid1: TStringGrid
    Left = 24
    Top = 56
    Width = 289
    Height = 233
    ColCount = 9
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
  end
  object StringGrid2: TStringGrid
    Left = 360
    Top = 56
    Width = 289
    Height = 225
    ColCount = 4
    FixedCols = 0
    RowCount = 2
    TabOrder = 1
  end
  object SpinEdit1: TSpinEdit
    Left = 32
    Top = 24
    Width = 121
    Height = 22
    MaxValue = 999
    MinValue = 1
    TabOrder = 2
    Value = 1
    OnChange = SpinEdit1Change
  end
  object BitBtn1: TBitBtn
    Left = 296
    Top = 8
    Width = 81
    Height = 33
    Caption = #1059#1087#1086#1088#1103#1076#1086#1095#1080#1090#1100
    TabOrder = 3
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 40
    Top = 296
    Width = 73
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 4
    OnClick = BitBtn2Click
  end
  object BitBtn3: TBitBtn
    Left = 232
    Top = 296
    Width = 65
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 5
    OnClick = BitBtn3Click
  end
  object BitBtn4: TBitBtn
    Left = 360
    Top = 296
    Width = 89
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 6
    OnClick = BitBtn4Click
  end
  object BitBtn5: TBitBtn
    Left = 472
    Top = 296
    Width = 81
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 7
    OnClick = BitBtn5Click
  end
  object BitBtn6: TBitBtn
    Left = 576
    Top = 296
    Width = 65
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 8
    OnClick = BitBtn6Click
  end
  object BitBtn7: TBitBtn
    Left = 136
    Top = 296
    Width = 73
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 9
    OnClick = BitBtn7Click
  end
  object OpenDialog1: TOpenDialog
    Left = 776
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    Left = 744
    Top = 8
  end
end
