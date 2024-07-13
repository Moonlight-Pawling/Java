package com.pawlingcastella.calculator

import android.app.Activity
import android.content.Intent
import android.content.SharedPreferences
import android.content.res.Configuration
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.media.MediaScannerConnection
import android.net.Uri
import android.os.Bundle
import android.util.Patterns
import android.view.Menu
import android.view.MenuItem
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.Toast
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.res.ResourcesCompat
import androidx.preference.PreferenceManager
import com.pawlingcastella.calculator.databinding.ActivityEditBinding
import java.io.File
import java.io.FileNotFoundException
import java.io.FileOutputStream
import java.io.IOException
import java.util.Locale

class EditActivity : AppCompatActivity() {
    private lateinit var binding: ActivityEditBinding
    private lateinit var changePhotoButton: ImageButton
    private lateinit var deletePhotoButton: ImageButton
    private lateinit var imageViewInEditActivity: ImageView
    private lateinit var imageFile: File
    private val fileName = "official_profile_image.png"
    private lateinit var sharedPreferences: SharedPreferences
    private var defaultName = "Angelo Vera Pawling"
    private var defaultEmail = "zS21027320@estudiantes.uv.com"
    private var defaultWebSite = "https://miuv.com"
    private var defaultPhone = "+52 2291590846"
    private var defaultLat: Double = 19.16571861761356
    private var defaultLon: Double = -96.11419823223545

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityEditBinding.inflate(layoutInflater)
        setContentView(binding.root)

        supportActionBar?.let {
            it.setDisplayHomeAsUpEnabled(true)
            it.title = getString(R.string.edit_profile)
        }

        val storageDirectory = filesDir
        val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))

        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this)
        imageViewInEditActivity = findViewById(R.id.edit_profile_picture)
        changePhotoButton = findViewById(R.id.profile_editview_change_photo_button)
        deletePhotoButton = findViewById(R.id.profile_editview_delete_photo_button)
        imageFile = File(imageDirectory, fileName)

        setImageViewFromLocalFile()
        setFocusLats()
        setDataBinding()

        changePhotoButton.setOnClickListener {
            pickImage()
        }

        deletePhotoButton.setOnClickListener {
            removeImage()
            imageViewInEditActivity.setImageDrawable(
                ResourcesCompat.getDrawable(
                    resources,
                    R.drawable.feminine_img_avatar,
                    null
                )
            )
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_edit, menu)
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.action_save -> {
                if (dataValidation()) {
                    saveSharedPreferences()
                    sendData()
                }
                true
            }

            R.id.action_change_language -> {
                showLanguageChangeDialog()
                true
            }

            android.R.id.home -> {
                onBackPressedDispatcher.onBackPressed()
                true
            }

            else -> super.onOptionsItemSelected(item)
        }
    }

    private fun setDataBinding() {
        binding.profileEditviewNameEditTextfield.setText(
            sharedPreferences.getString(
                getString(R.string.key_name),
                defaultName
            )
        )
        binding.profileEditviewEmailEditTextfield.setText(
            sharedPreferences.getString(
                getString(R.string.key_email),
                defaultEmail
            )
        )
        binding.profileEditviewWebsiteEditTextfield.setText(
            sharedPreferences.getString(
                getString(R.string.key_website),
                defaultWebSite
            )
        )
        binding.profileEditviewPhoneEditTextfield.setText(
            sharedPreferences.getString(
                getString(R.string.key_phone),
                defaultPhone
            )
        )
        binding.profileEditviewLatEditTextfield.setText(
            sharedPreferences.getString(
                getString(R.string.key_lat),
                defaultLat.toString()
            )
        )
        binding.profileEditviewLonEditTextfield.setText(
            sharedPreferences.getString(
                getString(R.string.key_lon),
                defaultLon.toString()
            )
        )
    }

    private fun showLanguageChangeDialog() {
        val languages = arrayOf("English", "Español")
        val builder = AlertDialog.Builder(this)
        builder.setTitle(getString(R.string.change_language))
        builder.setItems(languages) { _, which ->
            when (which) {
                0 -> changeLanguage("en")
                1 -> changeLanguage("es")
            }
        }
        builder.show()
    }

    private fun changeLanguage(language: String) {
        val locale = Locale(language)
        Locale.setDefault(locale)
        val config = Configuration()
        config.locale = locale
        resources.updateConfiguration(config, resources.displayMetrics)
        val refresh = Intent(this, EditActivity::class.java)
        startActivity(refresh)
        finish()
    }

    private fun removeImage() {
        val storageDirectory = filesDir
        val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))
        val imageFile = File(imageDirectory, fileName)

        if (imageFile.exists()) {
            imageFile.delete()
            MediaScannerConnection.scanFile(this, arrayOf(imageFile.absolutePath), null, null)
            Toast.makeText(
                this,
                getString(R.string.toast_text_image_deleted_successfully), Toast.LENGTH_SHORT
            ).show()
        } else {
            Toast.makeText(
                this,
                getString(R.string.toast_text_no_image_to_delete), Toast.LENGTH_SHORT
            ).show()
        }
    }

    private fun setFocusLats() {
        binding.profileEditviewNameEditTextfield.setOnFocusChangeListener { _, isFocused ->
            if (isFocused) {
                binding.profileEditviewNameEditTextfield.text?.let {
                    binding.profileEditviewNameEditTextfield.setSelection(
                        it.length
                    )
                }
            }
        }

        binding.profileEditviewEmailEditTextfield.setOnFocusChangeListener { _, isFocused ->
            if (isFocused) {
                binding.profileEditviewEmailEditTextfield.text?.let {
                    binding.profileEditviewEmailEditTextfield.setSelection(
                        it.length
                    )
                }
            }
        }

        binding.profileEditviewWebsiteEditTextfield.setOnFocusChangeListener { _, isFocused ->
            if (isFocused) {
                binding.profileEditviewWebsiteEditTextfield.text?.let {
                    binding.profileEditviewWebsiteEditTextfield.setSelection(
                        it.length
                    )
                }
            }
        }

        binding.profileEditviewPhoneEditTextfield.setOnFocusChangeListener { _, isFocused ->
            if (isFocused) {
                binding.profileEditviewPhoneEditTextfield.text?.let {
                    binding.profileEditviewPhoneEditTextfield.setSelection(
                        it.length
                    )
                }
            }
        }

        binding.profileEditviewLatEditTextfield.setOnFocusChangeListener { _, isFocused ->
            if (isFocused) {
                binding.profileEditviewLatEditTextfield.text?.let {
                    binding.profileEditviewLatEditTextfield.setSelection(
                        it.length
                    )
                }
            }
        }

        binding.profileEditviewLonEditTextfield.setOnFocusChangeListener { _, isFocused ->
            if (isFocused) {
                binding.profileEditviewLonEditTextfield.text?.let {
                    binding.profileEditviewLonEditTextfield.setSelection(
                        it.length
                    )
                }
            }
        }
    }

    private fun checkForExistingImage(fileName: String): Boolean {
        val storageDirectory = filesDir
        val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))

        val imageFile = File(imageDirectory, fileName)
        return imageFile.exists()
    }

    private fun setImageViewFromLocalFile() {
        val doesExist = checkForExistingImage(fileName)
        if (doesExist) {
            try {
                val bitmap = BitmapFactory.decodeFile(imageFile.absolutePath)
                imageViewInEditActivity.setImageBitmap(bitmap)
            } catch (e: FileNotFoundException) {
                e.printStackTrace()
            }
        } else {
            binding.editProfilePicture.setImageDrawable(
                ResourcesCompat.getDrawable(
                    resources,
                    R.drawable.feminine_img_avatar,
                    null
                )
            )
        }
    }

    private fun pickImage() {
        val intent = Intent(Intent.ACTION_PICK)
        intent.type = "image/*"
        pickMediaLauncher.launch(intent)
    }

    private val pickMediaLauncher: ActivityResultLauncher<Intent> =
        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                val data = result.data
                val imageUri = data?.data
                if (imageUri != null) {
                    saveImage(imageUri)
                }
            }
        }

    private fun saveImage(imageUri: Uri) {
        try {
            val inputStream = contentResolver.openInputStream(imageUri)
            val bitmap = BitmapFactory.decodeStream(inputStream)
            val storageDirectory = filesDir
            val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))
            if (!imageDirectory.exists()) {
                imageDirectory.mkdirs()
            }
            val imageFile = File(imageDirectory, fileName)
            val outputStream = FileOutputStream(imageFile)
            bitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream)
            MediaScannerConnection.scanFile(this, arrayOf(imageFile.absolutePath), null, null)
            Toast.makeText(
                this,
                getString(R.string.toast_text_image_saved_successfully), Toast.LENGTH_SHORT
            ).show()
        } catch (e: FileNotFoundException) {
            e.printStackTrace()
            Toast.makeText(
                this,
                getString(R.string.toast_text_error_saving_image), Toast.LENGTH_SHORT
            ).show()
        } catch (e: IOException) {
            e.printStackTrace()
            Toast.makeText(
                this,
                getString(R.string.toast_text_error_saving_image), Toast.LENGTH_SHORT
            ).show()
        }
        setImageViewFromLocalFile()
    }

    private fun saveSharedPreferences() {
        val sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this)
        with(sharedPreferences.edit()) {
            putString(
                getString(R.string.key_name),
                binding.profileEditviewNameEditTextfield.text.toString().trim()
            )
            putString(
                getString(R.string.key_email),
                binding.profileEditviewEmailEditTextfield.text.toString().trim()
            )
            putString(
                getString(R.string.key_website),
                binding.profileEditviewWebsiteEditTextfield.text.toString().trim()
            )
            putString(
                getString(R.string.key_phone),
                binding.profileEditviewPhoneEditTextfield.text.toString().trim()
            )
            putString(
                getString(R.string.key_lat),
                binding.profileEditviewLatEditTextfield.text.toString().trim()
            )
            putString(
                getString(R.string.key_lon),
                binding.profileEditviewLonEditTextfield.text.toString().trim()
            )
            apply()
        }
    }

    private fun sendData() {
        val intent = Intent()
        setResult(RESULT_OK, intent)
        finish()
    }

    private fun dataValidation(): Boolean {
        var validationBooleanStatus = true

        val nombre = binding.profileEditviewNameEditTextfield.text.toString().trim()
        if (nombre.length < 3 && nombre.isNotEmpty()) {
            binding.profileEditviewNameTextfield.run {
                error = context.getString(R.string.validation_name_1)
                requestFocus()
            }
            validationBooleanStatus = false
        } else if (nombre.isEmpty()) {
            binding.profileEditviewNameTextfield.run {
                error = context.getString(R.string.validation_name_2)
                requestFocus()
            }
            validationBooleanStatus = false
        } else {
            binding.profileEditviewNameTextfield.error = null
        }

        if (Patterns.EMAIL_ADDRESS.matcher(
                binding.profileEditviewEmailEditTextfield.text.toString().trim()
            ).matches() && binding.profileEditviewEmailEditTextfield.text.toString().trim()
                .isNotEmpty()
        ) {
            binding.profileEditviewEmailTextfield.error = null
        } else if (binding.profileEditviewEmailEditTextfield.text.toString().trim()
                .isNullOrEmpty()
        ) {
            binding.profileEditviewEmailTextfield.run {
                error = context.getString(R.string.validation_email_1)
                requestFocus()
            }
            validationBooleanStatus = false
        } else {
            binding.profileEditviewEmailTextfield.run {
                error = context.getString(R.string.validation_email_2)
                requestFocus()
            }
            validationBooleanStatus = false
        }

        if (Patterns.WEB_URL.matcher(
                binding.profileEditviewWebsiteEditTextfield.text.toString().trim()
            ).matches() && binding.profileEditviewWebsiteEditTextfield.text.toString().trim()
                .isNotEmpty()
        ) {
            binding.profileEditviewWebsiteTextfield.error = null
        } else if (binding.profileEditviewWebsiteEditTextfield.text.toString().trim()
                .isNullOrEmpty()
        ) {
            binding.profileEditviewWebsiteTextfield.run {
                error = context.getString(R.string.validation_website_1)
                requestFocus()
            }
            validationBooleanStatus = false
        } else {
            binding.profileEditviewWebsiteTextfield.run {
                error = context.getString(R.string.validation_website_2)
                requestFocus()
            }
            validationBooleanStatus = false
        }

        val telephonicnumber = binding.profileEditviewPhoneEditTextfield.text.toString().trim()
        if (Patterns.PHONE.matcher(binding.profileEditviewPhoneEditTextfield.text.toString().trim())
                .matches() && binding.profileEditviewPhoneEditTextfield.text.toString()
                .isNotEmpty() && telephonicnumber.length >= 7
        ) {
            binding.profileEditviewPhoneTextfield.error = null
        } else if (binding.profileEditviewPhoneEditTextfield.text.toString().trim()
                .isNullOrEmpty()
        ) {
            binding.profileEditviewPhoneTextfield.run {
                error = context.getString(R.string.validation_phone_1)
                requestFocus()
            }
            validationBooleanStatus = false
        } else if (telephonicnumber.length < 7) {
            binding.profileEditviewPhoneTextfield.run {
                error = context.getString(R.string.validation_phone_2)
                requestFocus()
            }
            validationBooleanStatus = false
        } else {
            binding.profileEditviewPhoneTextfield.run {
                error = context.getString(R.string.validation_phone_3)
                requestFocus()
            }
            validationBooleanStatus = false
        }

        if (binding.profileEditviewLatEditTextfield.text.toString()
                .matches(Regex("^(-?[0-9]+)(\\.[0-9]+)\$")) && binding.profileEditviewLatEditTextfield.text.toString()
                .isNotEmpty() && (binding.profileEditviewLatEditTextfield.text.toString()
                .toDouble() <= 90 && binding.profileEditviewLatEditTextfield.text.toString()
                .toDouble() >= -90)
        ) {
            binding.profileEditviewLatTextfield.error = null
        } else if (binding.profileEditviewLatEditTextfield.text.isNullOrEmpty()) {
            binding.profileEditviewLatTextfield.run {
                error = context.getString(R.string.validation_lat_1)
                requestFocus()
            }
            validationBooleanStatus = false
        } else if (binding.profileEditviewLatEditTextfield.text.toString()
                .toDouble() > 90 || binding.profileEditviewLatEditTextfield.text.toString()
                .toDouble() < -90
        ) {
            binding.profileEditviewLatTextfield.run {
                error = context.getString(R.string.validation_lat_2)
                requestFocus()
            }
            validationBooleanStatus = false
        } else if (!(binding.profileEditviewLatEditTextfield.text.toString()
                .matches(Regex("^(-?[0-9]+)(\\.[0-9]+)\$")))
        ) {
            binding.profileEditviewLatTextfield.run {
                error = context.getString(R.string.validation_lat_3)
                requestFocus()
            }
            validationBooleanStatus = false
        }

        if (binding.profileEditviewLonEditTextfield.text.toString()
                .matches(Regex("^(-?[0-9]+)(\\.[0-9]+)\$")) && binding.profileEditviewLonEditTextfield.text.toString()
                .isNotEmpty() && (binding.profileEditviewLonEditTextfield.text.toString()
                .toDouble() <= 180 && binding.profileEditviewLonEditTextfield.text.toString()
                .toDouble() >= -180)
        ) {
            binding.profileEditviewLonTextfield.error = null
        } else if (binding.profileEditviewLonEditTextfield.text.isNullOrEmpty()) {
            binding.profileEditviewLonTextfield.run {
                error = context.getString(R.string.validation_lon_1)
                requestFocus()
            }
            validationBooleanStatus = false
        } else if (binding.profileEditviewLonEditTextfield.text.toString()
                .toDouble() > 180 || binding.profileEditviewLonEditTextfield.text.toString()
                .toDouble() < -180
        ) {
            binding.profileEditviewLonTextfield.run {
                error = context.getString(R.string.validation_lon_2)
                requestFocus()
            }
            validationBooleanStatus = false
        } else if (!(binding.profileEditviewLonEditTextfield.text.toString()
                .matches(Regex("^(-?[0-9]+)(\\.[0-9]+)\$")))
        ) {
            binding.profileEditviewLonTextfield.run {
                error = context.getString(R.string.validation_lon_3)
                requestFocus()
            }
            validationBooleanStatus = false
        }

        return validationBooleanStatus
    }
}


