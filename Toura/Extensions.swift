//
//  Extensions.swift
//  Toura
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 02/12/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

//
//  Extensions.swift
//  FindMyCar
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 28/11/17.
//  Copyright © 2017 Deloitte Digital(India). All rights reserved.
//

import Foundation
import UIKit

//MARK: -UISearchBar Extension
extension UISearchBar {
    func changeSearchbarIcon(image : UIImage)
    {
        self.tintColor = UIColor.clear
        for subview in self.subviews
        {
            for view in subview.subviews
            {
                if let searchField = view as? UITextField
                {
                    let imageView = UIImageView()
                    imageView.image = image;
                    imageView.frame = CGRect(x: 0, y: 0, width: image.size.width/1.5, height: image.size.height/1.5)
                    searchField.leftView = imageView
                    searchField.leftViewMode = UITextFieldViewMode.always
                }
            }
        }
    }
}
//MARK: -Switch Class
open class CheckBox: UIButton {
    // Images
    open var checkedImage = UIImage(named: "Checkbox-active")
    open var uncheckedImage = UIImage(named: "Checkbox-Inactive")
    
    @IBInspectable
    open var checkedCheckBox: UIImage? = UIImage(named: "Checkbox-active") {
        didSet {
            checkedImage = checkedCheckBox
        }
    }
    
    @IBInspectable
    open var unCheckedCheckBox: UIImage? = UIImage(named: "Checkbox-Inactive") {
        didSet {
            uncheckedImage = unCheckedCheckBox
        }
    }
    
    
    // Bool property
    public var isChecked: Bool = false {
        didSet{
            if isChecked == true {
                self.setImage(checkedImage, for: .normal)
            } else {
                self.setImage(uncheckedImage, for: .normal)
            }
        }
    }
    
    override open func awakeFromNib() {
        self.addTarget(self, action: #selector(buttonClicked(sender:)), for: UIControlEvents.touchUpInside)
        self.isChecked = false;
    }
    
    @objc func buttonClicked(sender: UIButton) {
        if sender == self {
            isChecked = !isChecked
        }
    }
}


/* Extension over UIColor to provide aux methods */
extension UIColor{
    
    public static func fromHex(_ hex:String) -> UIColor {
        var cString:String = hex.trimmingCharacters(in: .whitespacesAndNewlines).uppercased()
        
        if (cString.hasPrefix("#")) {
            cString.remove(at: cString.startIndex)
        }
        
        if ((cString.characters.count) != 6) {
            return UIColor.gray
        }
        
        var rgbValue:UInt32 = 0
        Scanner(string: cString).scanHexInt32(&rgbValue)
        
        return UIColor(
            red: CGFloat((rgbValue & 0xFF0000) >> 16) / 255.0,
            green: CGFloat((rgbValue & 0x00FF00) >> 8) / 255.0,
            blue: CGFloat(rgbValue & 0x0000FF) / 255.0,
            alpha: CGFloat(1.0)
        )
    }
    
    public func hexString(_ includeAlpha: Bool = true) -> String {
        var r: CGFloat = 0
        var g: CGFloat = 0
        var b: CGFloat = 0
        var a: CGFloat = 0
        self.getRed(&r, green: &g, blue: &b, alpha: &a)
        
        if (includeAlpha) {
            return String(format: "#%02X%02X%02X%02X", Int(r * 255), Int(g * 255), Int(b * 255), Int(a * 255))
        } else {
            return String(format: "#%02X%02X%02X", Int(r * 255), Int(g * 255), Int(b * 255))
        }
    }
}

//Make Navbar Transparent
extension UIViewController{
    func transparentNavigationBar(){
        self.navigationController?.navigationBar.setBackgroundImage(UIImage(), for: .default)
        self.navigationController?.navigationBar.shadowImage = UIImage()
        self.navigationController?.navigationBar.isTranslucent = true
        self.navigationController?.view.backgroundColor = UIColor.clear
        self.navigationController?.navigationBar.backgroundColor = UIColor.clear
    }
}
