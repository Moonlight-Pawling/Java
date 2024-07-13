package com.pawlingcastella.calculator

import android.app.SearchManager
import android.content.Intent
import android.content.SharedPreferences
import android.content.res.Configuration
import android.graphics.BitmapFactory
import android.media.MediaScannerConnection
import android.net.Uri
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.res.ResourcesCompat
import androidx.preference.PreferenceManager.getDefaultSharedPreferences
import com.pawlingcastella.calculator.databinding.ActivityAboutBinding
import java.io.File
import java.io.FileNotFoundException
import java.util.Locale

class AboutActivity : AppCompatActivity() {
    private lateinit var binding: ActivityAboutBinding
    private lateinit var sharedPreferences: SharedPreferences
    private lateinit var imageViewInAboutActivity: ImageView
    private var googleMapsButtonState: Boolean = false
    private lateinit var imageFile: File
    private val fileName = "official_profile_image.png"
    private var defaultName = "Angelo Vera Pawling"
    private var defaultEmail = "zS21027320@estudiantes.uv.com"
    private var defaultWebSite = "https://miuv.com"
    private var defaultPhone = "+52 2291590846"
    private var defaultLat: Double = 19.16571861761356
    private var defaultLon: Double = -96.11419823223545

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityAboutBinding.inflate(layoutInflater)
        setContentView(binding.root)

        supportActionBar?.let {
            it.setDisplayHomeAsUpEnabled(true)
            it.title = getString(R.string.about_activity_name)
        }

        val storageDirectory = filesDir
        val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))

        sharedPreferences = getDefaultSharedPreferences(this)
        imageViewInAboutActivity = findViewById(R.id.profile_mainview_profilepicture)
        imageFile = File(imageDirectory, fileName)

        getSharedPreferences()
        setImageViewFromLocalFile()
        setupIntent()
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_about, menu)
        return true
    }

    override fun onResume() {
        super.onResume()
        getSharedPreferences()
        setImageViewFromLocalFile()
        setupIntent()
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            android.R.id.home -> {
                onBackPressedDispatcher.onBackPressed()
                true
            }

            R.id.action_edit -> {
                val intent = Intent(this, EditActivity::class.java)
                editResult.launch(intent)
                true
            }

            R.id.action_delete -> {
                sharedPreferences.edit().clear().apply()
                removeImage()
                getSharedPreferences()
                googleMapsButtonState = false
                binding.profileMainviewShowGoogleMaps.text = getString(R.string.text_show_location)
                setImageViewFromLocalFile()
                Toast.makeText(this, getString(R.string.delete_profile_info), Toast.LENGTH_SHORT)
                    .show()
                true
            }

            R.id.action_change_language -> {
                showLanguageChangeDialog()
                true
            }

            else -> super.onOptionsItemSelected(item)
        }
    }

    private val editResult =
        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) {
            if (it.resultCode == RESULT_OK) {
                setImageViewFromLocalFile()
                getSharedPreferences()
                googleMapsButtonState = false
                binding.profileMainviewShowGoogleMaps.text = getString(R.string.text_show_location)
            }
        }

    private fun setImageViewFromLocalFile() {
        val doesExist = checkForExistingImage(fileName)
        if (doesExist) {
            try {
                val bitmap = BitmapFactory.decodeFile(imageFile.absolutePath)
                imageViewInAboutActivity.setImageBitmap(bitmap)
            } catch (e: FileNotFoundException) {
                e.printStackTrace()
            }
        } else {
            binding.profileMainviewProfilepicture.setImageDrawable(
                ResourcesCompat.getDrawable(
                    resources,
                    R.drawable.feminine_img_avatar,
                    null
                )
            )
        }
    }

    private fun checkForExistingImage(fileName: String): Boolean {
        val storageDirectory = filesDir
        val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))
        val imageFile = File(imageDirectory, fileName)
        return imageFile.exists()
    }

    private fun removeImage() {
        val storageDirectory = filesDir
        val imageDirectory = File(storageDirectory, getString(R.string.profile_picture_path))
        val imageFile = File(imageDirectory, fileName)

        if (imageFile.exists()) {
            imageFile.delete()
            MediaScannerConnection.scanFile(this, arrayOf(imageFile.absolutePath), null, null)
        }
    }

    private fun getSharedPreferences() {
        val sharedPreferences = getDefaultSharedPreferences(this)
        val sharedPrefName = sharedPreferences.getString(getString(R.string.key_name), defaultName)
        val sharedPrefEmail =
            sharedPreferences.getString(getString(R.string.key_email), defaultEmail)
        val sharedPrefWebsite =
            sharedPreferences.getString(getString(R.string.key_website), defaultWebSite)
        val sharedPrefPhone =
            sharedPreferences.getString(getString(R.string.key_phone), defaultPhone)
        val sharedPrefLat =
            sharedPreferences.getString(getString(R.string.key_lat), defaultLat.toString())
        val sharedPrefLon =
            sharedPreferences.getString(getString(R.string.key_lon), defaultLon.toString())
        updateUI(sharedPrefName!!, sharedPrefEmail!!, sharedPrefWebsite!!, sharedPrefPhone!!)
    }

    private fun updateUI(
        name: String = "Angelo Vera Pawling",
        email: String = "zS21027320@estudiantes.uv.com",
        website: String = "https://www.miuv.com",
        phone: String = "+52 2291590846"
    ) {
        binding.profileMainviewName.text = name
        binding.profileMainviewEmail.text = email
        binding.profileMainviewWebsite.text = website
        binding.profileMainviewPhone.text = phone
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

        val refresh = Intent(this, AboutActivity::class.java)
        startActivity(refresh)
        finish()
    }

    private fun launchIntent(intent: Intent) {
        if (intent.resolveActivity(packageManager) != null) {
            startActivity(intent)
        } else {
            Toast.makeText(
                this,
                getString(R.string.compatible_app_not_found_text),
                Toast.LENGTH_SHORT
            ).show()
        }
    }

    private fun setupIntent() {
        binding.profileMainviewName.setOnClickListener {
            val intent = Intent(Intent.ACTION_WEB_SEARCH).apply {
                putExtra(SearchManager.QUERY, binding.profileMainviewName.text)
            }
            launchIntent(intent)
        }

        binding.profileMainviewEmail.setOnClickListener {
            val intent = Intent(Intent.ACTION_SENDTO).apply {
                data = Uri.parse("mailto:")
                putExtra(Intent.EXTRA_EMAIL, binding.profileMainviewEmail.text.toString())
                putExtra(Intent.EXTRA_SUBJECT, "Automatic INTENT")
                putExtra(Intent.EXTRA_TEXT, "Example text here")
            }
            launchIntent(intent)
        }

        binding.profileMainviewWebsite.setOnClickListener {
            val webText = Uri.parse(binding.profileMainviewWebsite.text.toString())
            val intent = Intent(Intent.ACTION_VIEW, webText)
            launchIntent(intent)
        }

        binding.profileMainviewPhone.setOnClickListener {
            val intent = Intent(Intent.ACTION_DIAL).apply {
                val phone = (it as TextView).text
                data = Uri.parse("tel:$phone")
            }
            launchIntent(intent)
        }

        binding.profileMainviewShowGoogleMaps.setOnClickListener {
            if (!googleMapsButtonState) {
                val sharedPrefLat =
                    sharedPreferences.getString(getString(R.string.key_lat), defaultLat.toString())
                val sharedPrefLon =
                    sharedPreferences.getString(getString(R.string.key_lon), defaultLon.toString())
                binding.profileMainviewShowGoogleMaps.text =
                    "Lat: $sharedPrefLat \nLon: $sharedPrefLon"
                googleMapsButtonState = true
                val mapCordinates = "$sharedPrefLat, $sharedPrefLon"
                val gmmIntentUri =
                    Uri.parse("geo:$sharedPrefLat,$sharedPrefLon?q=$mapCordinates?z=17")
                val mapIntent = Intent(Intent.ACTION_VIEW, gmmIntentUri)
                mapIntent.setPackage("com.google.android.apps.maps")
                startActivity(mapIntent)
            } else {
                googleMapsButtonState = false
                binding.profileMainviewShowGoogleMaps.text = getString(R.string.text_show_location)
            }
        }
    }

}
